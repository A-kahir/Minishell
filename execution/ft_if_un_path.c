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
	int		flag_redir;
	int		status;
	char *command;
	int i;

	status = 0;
	in.status = ft_strdup(stat.status);
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (0);
	i = 0;
	while (i < in.n_cmds - 1)
		if (pipe(in.pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	if (data->type == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, line_env, env_here, in);
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
		if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			in.i = 0;
			while (in.i < in.n_cmds)
			{
				pid = fork();
				if (pid == -1)
					(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
					ft_child_pro(data, line_env, env_here, in);
				data = data->next;
				in.i++;
			}
			ft_close_pipes(in.pipes, in.n_cmds);
			while (wait(&status) > 0);
			status = status / 256;
			free(in.pipes);
		}
		if (data && ((ft_strcmp(command, "cmd") == 0 && flag_redir == 0) || data->builtin_type == 5))
			printf("minishell: %s: No such file or directory\n", data->cmd[0]);
		if (ft_strcmp(command, "built") == 0 && data->builtin_type != -1 && data->builtin_type != 5)
			ft_is_builtins_f(data, line_env, in);
		if (flag_redir == 1)
			status = ft_is_redir(data, line_env, env_here, stat);
	}
	free(in.status);
	return (status);
}
