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
	t_data *tmp;
	pid_t pid;
    int status;

	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		exit(1);
	in.i = 0;
	while (in.i < in.n_cmds - 1)
	{
		if (pipe(in.pipes[in.i]) == -1)
			(perror("Pipe creation failed"), exit(1));
		in.i++;
	}
	int *hered_fd = malloc(sizeof(int) * in.n_cmds);
	if (!hered_fd)
		exit(1);
	tmp = data;
	in.i = 0;
	while (in.i < in.n_cmds)
	{
		hered_fd[in.i] = -1;
		if (tmp->redir && tmp->redir->type == HEREDOC)
			hered_fd[in.i] = ft_handle_heredoc(tmp->redir->target);
		tmp = tmp->next;
		in.i++;
	}
	in.status = (char *)hered_fd;
	t_data *curr = data;
	in.i = 0;
	while (in.i < in.n_cmds)
	{
		pid = fork();
		if (pid == -1)
			(perror("Fork failed"), ft_close_pipes(in.pipes, in.n_cmds), exit(1));
		else if (pid == 0)
			ft_child_hered_bef(curr, line_env, env_here, in);
		curr = curr->next;
		in.i++;
	}
	ft_close_pipes(in.pipes, in.n_cmds);
	in.i = 0;
	while (in.i < in.n_cmds)
	{
		if (hered_fd[in.i] != -1)
			close(hered_fd[in.i]);
		in.i++;
	}
	while (wait(&status) > 0)
        ;
    status = status / 256;
	free(in.pipes);
	free(hered_fd);
	return (status);
}
