/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:04:41 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:04:41 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
int ft_exec_normal(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	pid_t	pid;
	t_exec	in;
	int		flag_redir;
	int		status;
	int		last_status;

	status = 0;
	g_status = 0;
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = NULL;
	if (in.n_cmds > 1)
	{
		in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
		if (!in.pipes)
			return (free(in.status), 0);
		int i = 0;
		while (i < in.n_cmds - 1)
			if (pipe(in.pipes[i++]) == -1)
				(perror("Pipe creation failed"), exit(1));
	}
	if (data->type == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				ft_child_pro(data, line_env, env_here, in);
			}
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		if (in.pipes)
		{
			free(in.pipes);
			in.pipes = NULL;
		}
		while (wait(&status) > 0)
		{
			if (status == 2 || status == 3)
			{
				if (WIFSIGNALED(status) && g_status == 0)
				{
					if (WTERMSIG(status) == SIGINT)
					{
						write(2, "\n", 2);
					}
					else if(WTERMSIG(status) == SIGQUIT)
					{
						status = 0;
						break ;
					}
					status = 0;
				}
			}
			else if (status != 2 || status != 3)
			{
				status = status / 256;
			}
		}
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		char *command = ft_check_built_redir(data);
		if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			in.i = 0;
			while (in.i < in.n_cmds)
			{
				pid = fork();
				if (pid == -1)
					(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					ft_child_pro(data, line_env, env_here, in);
				}
				data = data->next;
				in.i++;
			}
			ft_close_pipes(in.pipes, in.n_cmds);
			if (in.pipes)
			{
				free(in.pipes);
				in.pipes = NULL;
			}
			int last_status;
			while (wait(&status) > 0)
			{
				if (status == 2 || status == 3)
				{
					if (WIFSIGNALED(status) && g_status == 0)
					{
						if (WTERMSIG(status) == SIGINT)
						{
							write(2, "\n", 2);
						}
						else if(WTERMSIG(status) == SIGQUIT)
						{
							write(2, "Quit:3\n", 8);
						}
						status = status + 128;
					}
				}
				else if (status != 2 || status != 3)
					status = status / 256;
			}
		}
		if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		{
			status = ft_is_builtins(data, line_env, in);
		}
		if (flag_redir == 1)
			status = ft_is_redir(data, line_env, env_here, stat);
	}
	if (in.pipes)
		in.pipes = NULL;
	return (status);
}
