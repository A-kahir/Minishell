/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_before.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:11:24 by akahir            #+#    #+#             */
/*   Updated: 2025/06/10 18:11:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

int ft_heredoc_before(t_data *data, t_built *line_env, t_ex_othr env_here)
{
	t_exec in;
	t_data *curr = data;
	pid_t *pids;
	int status = 0;

	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (1);
	in.i = 0;
	while (in.i < in.n_cmds - 1)
	{
		if (pipe(in.pipes[in.i]) == -1)
			return (perror("Pipe creation failed"), free(in.pipes), 1);
		in.i++;
	}
	pids = malloc(sizeof(pid_t) * in.n_cmds);
	if (!pids)
		return (free(in.pipes), 1);
	in.i = 0;
	while (in.i < in.n_cmds)
	{
		pids[in.i] = fork();
		if (pids[in.i] == -1)
		{
			perror("Fork failed");
			ft_close_pipes(in.pipes, in.n_cmds);
			free(in.pipes);
			free(pids);
			return (1);
		}
		else if (pids[in.i] == 0)
			ft_child_hered_bef(curr, line_env, env_here, in);
		curr = curr->next;
		in.i++;
	}
	ft_close_pipes(in.pipes, in.n_cmds);
	in.i = 0;
	while (in.i < in.n_cmds)
	{
		waitpid(pids[in.i], &status, 0);
		in.i++;
	}
	status = status / 256;
	free(in.pipes);
	free(pids);
	return (status);
}
