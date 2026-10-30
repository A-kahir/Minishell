/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:06:40 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 19:23:12 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	ft_init_pipes(int (*pipes)[2], int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
}

int	ft_prepare_heredoc_fds(t_data *data, int *hered_fd,
t_built *line_env, t_exec stat)
{
	int		i;
	t_data	*tmp;
	t_redir	*redir;

	1 && (i = 0, tmp = data);
	while (i < ft_count_cmds(data))
	{
		hered_fd[i] = -1;
		redir = tmp->redir;
		while (redir)
		{
			if (redir->type == 3)
			{
				if (hered_fd[i] != -1)
					close(hered_fd[i]);
				hered_fd[i] = ft_handle_heredoc(redir->target, line_env, stat);
				if (hered_fd[i] == -1)
					return (1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

pid_t	ft_fork_heredoc(t_data *curr, t_built *line_env,
t_ex_othr env_here, t_exec in)
{
	pid_t		pid;
	pid_t		last_pid;
	t_pid_list	*lst_pids;

	1 && (in.i = 0, lst_pids = 0);
	while (curr)
	{
		pid = fork();
		if (pid == -1)
		{
			(perror("fork"), ft_close_fd_opening());
			(ft_close_pipes(in.pipes, in.n_cmds));
			return (ft_kill_p(lst_pids), 1);
		}
		else if (pid == 0)
		{
			(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
			ft_child_heredoc(curr, line_env, env_here, in);
		}
		else if (in.i == in.n_cmds - 1)
			last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		1 && (curr = curr->next, in.i++);
	}
	return (last_pid);
}

void	ft_close_her_fd(int *hered_fd, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		if (hered_fd[i] != -1)
			close(hered_fd[i]);
		i++;
	}
}

int	ft_heredoc(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
	t_exec			in;
	int				*hered_fd;
	pid_t			last_pid;
	t_data			*temp;
	int				status;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	1 && (status = 0, temp = data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc_cl(sizeof(int [2]) * (in.n_cmds - 1), ALLOCATE, 0);
	if (!in.pipes)
		(malloc_cl(0, 3, 0), exit(1));
	ft_init_pipes(in.pipes, in.n_cmds);
	hered_fd = malloc_cl(sizeof(int) * in.n_cmds, ALLOCATE, 1);
	if (!hered_fd)
		(malloc_cl(0, 3, 0), exit(1));
	if (ft_prepare_heredoc_fds(data, hered_fd, line_env, stat) == 1)
		return (1);
	in.status = (char *)hered_fd;
	last_pid = ft_fork_heredoc(data, line_env, env_here, in);
	(ft_close_pipes(in.pipes, in.n_cmds), ft_close_her_fd(hered_fd, in.n_cmds));
	status = ft_multiple_wait(temp, &in, status, last_pid);
	return (status);
}
