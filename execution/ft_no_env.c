/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:21 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:19:21 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_no_env_single_loop(t_data **data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t		pid;
	pid_t		last_pid;
	int			status;
	t_pid_list	*lst_pids;

	1 && (in->i = 0, status = 0, last_pid = 0, lst_pids = 0);
	while (in->i < in->n_cmds)
	{
		pid = ft_no_env_fork_child(*data, line_env, env_here, *in);
		if (pid == -1)
			return (ft_close_pipes(in->pipes, in->n_cmds),
				perror("Fork"), ft_close_fd_opening(),
				ft_kill_p(lst_pids), 1);
		else
			if (in->i == in->n_cmds - 1)
				last_pid = pid;
		lst_pids = ft_add_pid(lst_pids, pid);
		*data = (*data)->next;
		in->i++;
	}
	ft_close_pipes(in->pipes, in->n_cmds);
	status = ft_signle_wait(status, last_pid, in);
	return (status);
}

static int	ft_no_env_type_1(t_data **data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	char	*command;
	int		flag_redir;
	int		status;

	1 && (command = ft_check_built_redir(*data), status = 0);
	flag_redir = ft_flag_redir(*data);
	if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
	{
		status = ft_no_env_single_loop(data, line_env, env_here, in);
	}
	if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		status = ft_is_builtins(*data, line_env, *in);
	return (status);
}

static int	ft_no_env_redir(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec stat)
{
	int	status;

	status = 0;
	if (ft_flag_redir(data) == 1)
		status = ft_is_redir(data, line_env, env_here, stat);
	return (status);
}

int	ft_no_env(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	t_exec			in;
	int				flag_redir;
	int				status;
	int				init_result;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	1 && (flag_redir = ft_flag_redir(data), status = 0);
	in.n_cmds = ft_count_cmds(data);
	init_result = ft_init_no_env(&in, &env_here, line_env, stat);
	in.status = ft_strdup(stat.status, 0, 0);
	if (init_result != 0)
		return (init_result);
	if (data->type == 0 && flag_redir == 0)
	{
		return (ft_no_env_type_0(&data, line_env, env_here, &in));
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		status = ft_no_env_type_1(&data, line_env, env_here, &in);
		if (flag_redir == 1)
			status = ft_no_env_redir(data, line_env, env_here, stat);
	}
	return (status);
}
