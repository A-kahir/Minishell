/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 22:43:38 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
void ft_is_builtins(t_data *data, t_built *line_env, char **env)
{
	static int flag_cd;
	t_built *temp;
	char *pwd_before_cd = NULL;

	if (data->builtin_type == 1) // cd
	{
		temp = line_env;
		while (temp)
		{
			if (ft_strcmp(temp->var, "PWD") == 0)
			{
				if (temp->value)
					pwd_before_cd = ft_strdup(temp->value);
				break;
			}
			temp = temp->next;
		}
		line_env = ft_cd(data->cmd, line_env);
		flag_cd = 1;
		// Now update old_pwd inside line_env with pwd_before_cd safely
		temp = line_env;
		while (temp)
		{
			if (ft_strcmp(temp->var, "OLDPWD") == 0)
			{
				if (temp->value)
					free(temp->value);
				temp->value = pwd_before_cd;
				break;
			}
			temp = temp->next;
		}
		if (!temp && pwd_before_cd)
		{
			// OLDPWD not found, add it front (using your ft_add_front function)
			line_env = ft_add_front(line_env, "OLDPWD", pwd_before_cd);
		}
	}
	else if (data->builtin_type == 0)
		ft_echo(data->cmd);
	else if (data->builtin_type == 2)
		ft_pwd(data->cmd);
	else if (data->builtin_type == 3)
		line_env = ft_export(line_env, data->cmd, flag_cd);
	else if (data->builtin_type == 4)
		line_env = ft_unset(line_env, data->cmd, env);
	else if (data->builtin_type == 5)
		line_env = ft_env(line_env);
	else if (data->builtin_type == 6)
		ft_exit(data->cmd);

	line_env = ft_update_exp(line_env, flag_cd);
	flag_cd = 0;
}
