/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cantinue_un_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:26:08 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 22:41:16 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_in_pp(t_exec *in, t_data *data)
{
	int	i;

	in->n_cmds = ft_count_cmds(data);
	in->pipes = malloc_cl(sizeof(int [2]) * (in->n_cmds - 1), ALLOCATE, 0);
	if (!in->pipes)
		return (0);
	i = 0;
	while (i < in->n_cmds - 1)
		if (pipe(in->pipes[i++]) == -1)
			return (perror("Pipe"), 1);
	return (1);
}

pid_t	ft_fork_and_child(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_child_pro_f(data, line_env, env_here, in);
	}
	return (pid);
}

int	ft_type_0(t_data **data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t		pid;
	int			status;
	t_pid_list	*lst_pids;
	pid_t		last_pid;

	1 && (in->i = 0, status = 0, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = ft_fork_and_child(*data, line_env, env_here, *in);
		if (pid == -1)
			return (ft_close_pipes(in->pipes, in->n_cmds), perror("Fork"),
				ft_close_fd_opening(), ft_kill_p(lst_pids), 1);
		else
			last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		*data = (*data)->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	status = ft_signle_wait(status, last_pid, in);
	return (status);
}

int	ft_exec_cmd_1(t_data **data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t		pid;
	int			status;
	t_pid_list	*lst_pids;
	pid_t		last_pid;

	1 && (in->i = 0, status = 0, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = ft_fork_and_child(*data, line_env, env_here, *in);
		if (pid == -1)
			return (ft_close_pipes(in->pipes, in->n_cmds), perror("Fork"),
				ft_close_fd_opening(), ft_kill_p(lst_pids), 1);
		else
			last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		*data = (*data)->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	status = ft_signle_wait(status, last_pid, in);
	return (status);
}
