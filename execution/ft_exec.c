/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:35:04 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 20:48:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void ft_exec(t_data *data, char **env, t_heredoc *heredoc)
{
	int		n_cmds;
	int		i;
	pid_t	pid;
	int		(*pipes)[2];

	i = 0;
	int flag_redir = ft_flag_redir(data);
	n_cmds = ft_count_cmds(data);
	pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
	while (i < n_cmds - 1)
		if (pipe(pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	if (data->type == 0 && flag_redir == 0)
	{
		i = 0;
		while (i < n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, pipes, i, n_cmds, env);
			data = data->next;
			i++;
		}
		ft_close_pipes(pipes, n_cmds);
		while (wait(NULL) > 0);
		free(pipes);
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		char *command = ft_check_built_redir(data, env);
		if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			i = 0;
			while (i < n_cmds)
			{
				pid = fork();
				if (pid == -1)
					(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
					ft_child_pro(data, pipes, i, n_cmds, env);
				data = data->next;
				i++;
			}
			ft_close_pipes(pipes, n_cmds);
			while (wait(NULL) > 0);
			free(pipes);
		}
		if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		{
			ft_is_builtins(data, env);
		}
		if (flag_redir == 1)
		{
			ft_is_redir(data, env, heredoc);
		}
	}
}
