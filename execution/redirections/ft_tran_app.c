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

pid_t	ft_fo_exe(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	t_data		*tmp;
	pid_t		pid;
	pid_t		last_pid;
	t_pid_list	*lst_pids;

	1 && (in->i = 0, tmp = data, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = ft_fork_child(tmp, line_env, env_here, in);
		if (pid == -1)
			return (ft_close_pipes(in->pipes, in->n_cmds - 1), perror("fork"),
				ft_close_fd_opening(), ft_kill_p(lst_pids), 1);
		else
			last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		tmp = tmp->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	return (last_pid);
}

pid_t	ft_handle_single_cmd(t_data *curr, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t		pid;
	pid_t		last_pid;
	t_pid_list	*lst_pids;

	lst_pids = 0;
	last_pid = 0;
	pid = fork();
	if (pid == -1)
		return (ft_close_pipes(in->pipes, in->n_cmds), perror("fork"),
			ft_close_fd_opening(), ft_kill_p(lst_pids), -1);
	else if (pid == 0)
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL),
			ft_child_redir(curr, line_env, env_here, *in));
	else
		last_pid = pid;
	lst_pids = ft_add_pid(lst_pids, pid);
	return (last_pid);
}

pid_t	ft_tran_handle_pipes(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t		last_pid;
	t_data		*curr;

	1 && (curr = data, last_pid = 0);
	if (in->n_cmds > 1)
	{
		in->pipes = malloc_cl(sizeof(int [2]) * (in->n_cmds - 1), ALLOCATE, 0);
		if (!in->pipes)
			perror("pipes");
		(ft_creat_pp(in), last_pid = ft_fo_exe(data, line_env, env_here, in));
		ft_close_pipes(in->pipes, in->n_cmds - 1);
	}
	else
		last_pid = ft_handle_single_cmd(curr, line_env, env_here, in);
	return (last_pid);
}

int	ft_tran_app(t_data *data, t_built *line_env, t_ex_othr env_here)
{
	int				status;
	t_exec			in;
	t_data			*curr;
	pid_t			last_pid;
	int				fd;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	curr = data;
	in.n_cmds = ft_count_cmds(data);
	if (curr->cmd == NULL && curr->redir
		&& curr->redir->target && in.n_cmds == 1)
	{
		fd = ft_fd_redirections(curr, curr->redir);
		if (fd == 1)
			return (1);
		write(1, "", 0);
		return (0);
	}
	last_pid = ft_tran_handle_pipes(data, line_env, env_here, &in);
	status = 0;
	status = ft_multiple_wait(data, &in, status, last_pid);
	return (status);
}
