/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tran_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 19:48:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_tran_app(t_data *data, t_built *line_env, t_ex_othr env_here)
{
	int status;
	t_exec in;
	t_data *curr;
	pid_t pid;

	curr = data;
	in.n_cmds = ft_count_cmds(data);
	if (in.n_cmds == 1)
	{
		if (curr->cmd == NULL)
		{
			if (curr->redir && curr->redir->target)
			{
				ft_fd_redirections(curr->redir);
				write(1, "", 0);
			}
			return (0);
		}
		if (ft_strcmp(curr->cmd[0], "echo") == 0 && curr->redir && curr->redir->target)
		{
			int i = 1;
			ft_fd_redirections(curr->redir);
			while (curr->cmd[i] != NULL)
			{
				int j = 0;
				while (curr->cmd[i][j] != '\0')
				{
					write(1, &curr->cmd[i][j], 1);
					j++;
				}
				if (curr->cmd[i + 1] != NULL)
					write(1, " ", 1);
				i++;
			}
			write(1, "\n", 1);
			return (0);
		}
		pid = fork();
		if (pid == -1)
			(perror("fork failed"), exit(1));
		if (pid == 0)
			ft_child_redir(curr, line_env, env_here, in);
		while (wait(&status) > 0);
		status = status / 256;
		return (status);
	}
	else
	{
		in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
		if (!in.pipes)
			(perror("malloc"), exit(1));
		in.i = 0;
		while (in.i < in.n_cmds - 1)
		{
			if (pipe(in.pipes[in.i]) == -1)
				return (perror("pipe creation failed"), free(in.pipes), 1);
			in.i++;
		}
		t_data *tmp = data;
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
			{
				ft_close_pipes(in.pipes, in.n_cmds - 1);
				(perror("fork failed"), free(in.pipes), exit(1));
			}
			if (pid == 0)
				ft_child_redir(tmp, line_env, env_here, in);
			tmp = tmp->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		free(in.pipes);
		while (wait(&status) > 0);
		status = status / 256;
	}
	return (status);
}
