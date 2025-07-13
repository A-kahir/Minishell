/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:29:01 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
static void	ft_save_oldpwd(t_built *temp, char *before_cd)
{
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
		{
			if (temp->value)
				free(temp->value);
			temp->value = before_cd;  // assumes before_cd is newly strdup'd
			return ;
		}
		temp = temp->next;
	}
}

static t_built	*ft_handle_cd(t_data *data, t_built *line_env, int *flag_cd)
{
	t_built	*temp;
	char	*before_cd;

	before_cd = NULL;
	temp = line_env;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0 && temp->value)
		{
			before_cd = ft_strdup(temp->value);
			break;
		}
		temp = temp->next;
	}
	line_env->old_pwd = ft_strdup(before_cd);
	line_env = ft_cd(data->cmd, line_env, flag_cd);
	if (*flag_cd == 1 && before_cd)
	{
		ft_save_oldpwd(line_env, ft_strdup(before_cd));  // duplicate to avoid double free
		line_env = ft_add_front(line_env, "OLDPWD", before_cd);
	}
	else
		free(before_cd);
	return (line_env);
}

int	ft_is_builtins(t_data *data, t_built *line_env, t_exec in)
{
	static int	flag_cd;

	if (!data)
		return (0);
	if (data->builtin_type == 1)
		line_env = ft_handle_cd(data, line_env, &flag_cd);
	else if (data->builtin_type == 0)
		ft_echo(data->cmd, in);
	else if (data->builtin_type == 2)
		ft_pwd(line_env);
	else if (data->builtin_type == 3)
		line_env = ft_export(line_env, data->cmd);
	else if (data->builtin_type == 4)
		line_env = ft_unset(line_env, data->cmd);
	else if (data->builtin_type == 5)
		line_env = ft_env(line_env);
	else if (data->builtin_type == 6)
	{
		in.status = ft_exit(data, in);
		return (ft_atoi(in.status));
	}
	line_env = ft_update_exp(line_env, flag_cd);
	flag_cd = 0;
	return (0);
}
