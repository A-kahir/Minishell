/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:21 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:19:21 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_no_env(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	pid_t	pid;
	t_exec	in;
	int		flag_redir;
	int		status;
	char	*command;
	int		i;

	status = 0;
	if (isatty(0))
		tcgetattr(0, &g_orig_term);
	in.status = ft_strdup(stat.status);
	if (!in.status)
		return (1);
	env_here.env = ft_fill_envp(line_env);
	if (!env_here.env)
		return (free(in.status), 1);
	command = ft_check_built_redir(data);
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (free(in.status), ft_free_split(env_here.env), 1);
	i = 0;
	while (i < in.n_cmds - 1)
	{
		if (pipe(in.pipes[i]) == -1)
		{
			return (perror("Pipe creation failed"),
			free(in.status), ft_free_split(env_here.env),
			free(in.pipes), exit(1), 1);
		}
		i++;
	}
	pid_t last_pid;
	if (data->type == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				return (ft_close_pipes(in.pipes, in.n_cmds),
				perror("Fork failed"), free(in.status),
				ft_free_split(env_here.env), free(in.pipes), 1);
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				ft_child_pro(data, line_env, env_here, in);
			}
			else
				if (in.i == in.n_cmds - 1)
					last_pid = pid;
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		t_data *tmp = data;
		status = ft_multiple_wait(tmp, in, status, last_pid);
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			in.i = 0;
			while (in.i < in.n_cmds)
			{
				pid = fork();
				if (pid == -1)
					return (ft_close_pipes(in.pipes, in.n_cmds),
					perror("Fork failed"), free(in.status),
					ft_free_split(env_here.env), free(in.pipes), 1);
				else if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					ft_child_pro(data, line_env, env_here, in);
				}
				else
					if (in.i == in.n_cmds - 1)
						last_pid = pid;
				data = data->next;
				in.i++;
			}
			ft_close_pipes(in.pipes, in.n_cmds);
			status = ft_signle_wait(status, last_pid);
		}
		if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
			status = ft_is_builtins(data, line_env, in);
		if (flag_redir == 1)
			status = ft_is_redir(data, line_env, env_here, stat);
	}
	ft_free_split(env_here.env);
	free(in.pipes);
	return (status);
}
