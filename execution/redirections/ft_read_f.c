/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:48 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:27:49 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_init_read(t_exec *in, int n_cmds)
{
	in->n_cmds = n_cmds;
	if (in->n_cmds == 0)
		return (0);
	in->pipes = malloc_cl(sizeof(int [2]) * (in->n_cmds - 1), ALLOCATE, 0);
	if (!in->pipes)
		return (perror("malloc failed"), 1);
	in->i = 0;
	while (in->i < in->n_cmds - 1)
	{
		if (pipe(in->pipes[in->i]) == -1)
		{
			ft_close_pipes(in->pipes, in->n_cmds);
			perror("Pipe");
			return (1);
		}
		in->i++;
	}
	return (2);
}

static int	ft_read_loop(t_data *curr, t_built *line_env,
	t_ex_othr env_here, t_exec *in)
{
	pid_t		last_pid;
	pid_t		pid;
	int			status;
	t_pid_list	*lst_pids;

	1 && (in->i = 0, status = 0, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = fork();
		if (pid == -1)
			(ft_close_pipes(in->pipes, in->n_cmds), perror("Fork"), status = 1,
				ft_close_fd_opening(), ft_kill_p(lst_pids));
		else if (pid == 0)
		{
			(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
			ft_child_read_f(curr, line_env, env_here, *in);
		}
		else if (in->i == in->n_cmds - 1)
			last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		curr = curr->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	return (ft_signle_wait(status, last_pid, in));
}

int	ft_read_f(t_data *data, t_built *line_env, t_ex_othr env_here)
{
	t_exec	in;
	int		init_result;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	init_result = ft_init_read(&in, ft_count_cmds(data));
	if (init_result != 2)
		return (init_result);
	return (ft_read_loop(data, line_env, env_here, &in));
}
