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

int ft_have_env(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
	int		flag_path;
	int		status;
	t_built *curr;

	env_here.env = ft_fill_envp(line_env);
	status = 0;
	flag_path = 0;
	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, "PATH") == 0)
			flag_path = 1;
		else if (curr->next == NULL && ft_strcmp(curr->var, "PATH") == 0 && ft_strcmp(curr->value, NULL) != 0)
			flag_path = 0;
		curr = curr->next;
	}
	if (flag_path == 1)
		status = ft_exec_normal(data, env_here, line_env, stat);
	else if (flag_path == 0)
		status = ft_if_un_path(data, env_here, line_env, stat);
	ft_free_split(env_here.env); 
	return (status);
}

int ft_exec(t_data *data, t_heredoc *heredoc, t_built *line_env, t_exec stat)
{
	t_ex_othr env_here;
	static int no_env;
	int status;

	env_here.heredoc = heredoc;
	status = 0;
	if ((ft_strcmp(line_env->var, "OLDPWD") == 0 && line_env->next == NULL) 
		|| (ft_strcmp(data->cmd[0], "env") == 0 && ft_strcmp(data->cmd[1], "-i") == 0)
		|| no_env == 1)
	{
		if (no_env == 0)
		{
			t_built *curr = line_env;
			while (curr)
			{
				if (ft_strcmp(curr->var, "PWD") != 0
					|| ft_strcmp(curr->var, "SHLVL") != 0
					|| ft_strcmp(curr->var, "OLDPWD") != 0)
						ft_rm_list(&line_env, curr);
				curr = curr->next;
			}
		}
		no_env = 1;
		status = ft_no_env(data, env_here, line_env, stat);
	}
	else if (no_env == 0)
	{
		status = ft_have_env(data, line_env, env_here, stat);
	}
	// printf("status ==> %d\n", status);
	return (status);
}
