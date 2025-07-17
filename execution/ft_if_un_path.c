/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_un_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:04:31 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:04:31 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_if_un_path(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	pid_t pid;
	t_exec in;
	int flag_redir;
	int status;
	char *command;
	int i;

	status = 0;
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (free(in.status), 0);
	i = 0;
	while (i < in.n_cmds - 1)
		if (pipe(in.pipes[i++]) == -1)
			return (perror("Pipe creation failed"), free(in.pipes), free(in.status), exit(1), 1);
	if (data->type == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				return (ft_close_pipes(in.pipes, in.n_cmds), free(in.pipes), free(in.status), perror("Fork failed"), exit(1), 1);
			else if (pid == 0)
				ft_child_pro_f(data, line_env, env_here, in);
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		while (wait(&status) > 0);
		status = status / 256;
		free(in.pipes);
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		command = ft_check_built_redir(data);
		if (command && ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			in.i = 0;
			while (in.i < in.n_cmds)
			{
				pid = fork();
				if (pid == -1)
					return (ft_close_pipes(in.pipes, in.n_cmds), free(in.pipes), free(in.status), perror("Fork failed"), 1);
				else if (pid == 0)
				{
					ft_child_pro_f(data, line_env, env_here, in);
				}
				data = data->next;
				in.i++;
			}
			ft_close_pipes(in.pipes, in.n_cmds);
			while (wait(&status) > 0);
			status = status / 256;
			free(in.pipes);
		}
		if (data && ((command && ft_strcmp(command, "cmd") == 0 && flag_redir == 0) || data->builtin_type == 5))
		{
			write(2, "minishell: ", 12);
			write(2, data->cmd[0], ft_strlen(data->cmd[0]));
			write(2, ": No such file or directory\n", 29);
			return (127);
		}
		if (command && ft_strcmp(command, "built") == 0 && data->builtin_type != -1 && data->builtin_type != 5)
			status = ft_is_builtins_f(data, line_env, in);
		if (flag_redir == 1)
			status = ft_is_redir(data, line_env, env_here, stat);
	}
	return (status);
}
