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

void ft_have_env(t_data *data, t_built *line_env, t_ex_othr env_here)
{
	int		flag_path;
	t_built *curr;

	env_here.env = ft_fill_envp(line_env);
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
		ft_exec_normal(data, env_here, line_env);
	else if (flag_path == 0)
		ft_if_un_path(data, env_here, line_env);
}

void ft_exec(t_data *data, t_heredoc *heredoc, t_built *line_env)
{
	t_ex_othr env_here;
	static int no_env;

	env_here.heredoc = heredoc;
	if ((ft_strcmp(line_env->var, "OLDPWD") == 0 && line_env->next == NULL) || no_env == 1)
	{
		no_env = 1;
		ft_no_env(data, env_here, line_env);
	}
	else if (no_env == 0)
	{
		ft_have_env(data, line_env, env_here);
	}
}
