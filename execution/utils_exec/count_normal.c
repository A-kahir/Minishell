/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:11:10 by akahir            #+#    #+#             */
/*   Updated: 2025/08/06 22:35:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_init_normal_setup(t_exec *in, t_data *data, t_exec stat)
{
	int	i;

	in->status = ft_strdup(stat.status, 0, 0);
	in->n_cmds = ft_count_cmds(data);
	in->pipes = malloc_cl(sizeof(int [2]) * (in->n_cmds - 1), ALLOCATE, 0);
	if (!in->pipes)
		return (0);
	i = 0;
	while (i < in->n_cmds - 1)
		if (pipe(in->pipes[i++]) == -1)
			return (perror("Pipe creation failed"), -1);
	return (1);
}

pid_t	ft_normal_fork_child(t_data *data, t_built *line_env,
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
		ft_child_pro(data, line_env, env_here, in);
	}
	return (pid);
}

int	ft_normal_type_0(t_data **data, t_built *line_env,
	t_ex_othr env_here, t_exec *in)
{
	pid_t		pid;
	pid_t		last_pid;
	t_data		*tmp;
	int			status;
	t_pid_list	*lst_pids;

	1 && (last_pid = 0, status = 0, in->i = 0, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = ft_normal_fork_child(*data, line_env, env_here, *in);
		if (pid == -1)
			return (ft_close_pipes(in->pipes, in->n_cmds), perror("Fork"),
				ft_close_fd_opening(), ft_kill_p(lst_pids), 1);
		else
			if (in->i == in->n_cmds - 1)
				last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		*data = (*data)->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	tmp = *data;
	status = ft_multiple_wait(tmp, in, status, last_pid);
	return (status);
}
