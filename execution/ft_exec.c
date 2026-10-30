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

int	ft_have_env(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec stat)
{
	int		flag_path;
	int		status;
	t_built	*curr;

	env_here.env = ft_fill_envp(line_env);
	1 && (status = 0, flag_path = 0);
	curr = line_env;
	while (curr)
	{
		if (curr->var && ft_strcmp(curr->var, "PATH") == 0)
		{
			if (curr->value)
				flag_path = 1;
			else
				flag_path = 0;
			break ;
		}
		curr = curr->next;
	}
	if (flag_path == 1)
		status = ft_exec_normal(data, env_here, line_env, stat);
	else if (flag_path == 0)
		status = ft_if_un_path(data, env_here, line_env, stat);
	ft_free_split(env_here.env);
	return (status);
}

int	ft_check_no_env(t_built *line_env)
{
	t_built	*curr;
	int		count;

	curr = line_env;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	if (count == 4 || count == 0 || count == 3)
		return (1);
	return (0);
}

static int	ft_exec_no_env(t_data *data, t_ex_othr env_here,
t_built *line_env, t_exec stat)
{
	t_built	*curr;
	int		flag_path;

	curr = line_env;
	flag_path = 0;
	while (curr)
	{
		if (curr->var && ft_strcmp(curr->var, "PATH") == 0)
		{
			if (curr->value)
				flag_path = 1;
			else
				flag_path = 0;
			break ;
		}
		curr = curr->next;
	}
	if (flag_path == 1)
		return (ft_no_env(data, env_here, line_env, stat));
	else
		return (ft_if_un_path(data, env_here, line_env, stat));
}

int	ft_exec(t_data *data, t_built *line_env, t_exec stat)
{
	t_ex_othr	env_here;
	static int	no_env;
	int			status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	no_env = 0;
	status = 0;
	env_here.env = NULL;
	if (ft_check_no_env(line_env) || no_env == 1)
	{
		no_env = 1;
		status = ft_exec_no_env(data, env_here, line_env, stat);
		ft_close_fd_opening();
		return (status);
	}
	else
		status = ft_have_env(data, line_env, env_here, stat);
	ft_close_fd_opening();
	return (status);
}
