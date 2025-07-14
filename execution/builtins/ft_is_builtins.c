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
			temp->value = before_cd;
			return ;
		}
		temp = temp->next;
	}
}

t_built	*ft_handle_cd(t_data *data, t_built *line_env, int *flag_cd, t_exec in)
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
	line_env = ft_cd(data->cmd, line_env, flag_cd, in);
	if (*flag_cd == 1 && before_cd)
	{
		ft_save_oldpwd(line_env, ft_strdup(before_cd));
		line_env = ft_add_front(line_env, "OLDPWD", before_cd);
	}
	else
		free(before_cd);
	return (line_env);
}

int	ft_is_builtins(t_data *data, t_built *line_env, t_exec in)
{
	static int	flag_cd;
	static int flag_one_pth;

	if (!data)
		return (0);
	t_built *curr = line_env;
	if (ft_strcmp(data->cmd[0], "export") == 0 && ft_strcmp(data->cmd[1], "PATH") == 0)
	{
		while (curr)
		{
			if (ft_strcmp(curr->var, "PATH") == 0
				&& ft_strcmp(curr->value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == 0)
			{
				flag_one_pth = 1;
				break;
			}
			curr = curr->next;
		}
	}
	if (data->builtin_type == 1)
	{
		line_env = ft_handle_cd(data, line_env, &flag_cd, in);
		line_env = ft_update_exp(line_env, flag_cd);
		return (ft_atoi(in.status));
	}
	else if (data->builtin_type == 0)
		ft_echo(data->cmd, in);
	else if (data->builtin_type == 2)
		ft_pwd(line_env);
	else if (data->builtin_type == 3)
	{
		if (ft_strcmp(data->cmd[0], "export") == 0 && data->cmd[1] == NULL)
		{
			ft_only_print(line_env, flag_one_pth);
			in.status = ft_strdup("0");
			return (ft_atoi(in.status));
		}
		line_env = ft_export(line_env, data->cmd, flag_one_pth, in);
		return (ft_atoi(in.status));
	}
	else if (data->builtin_type == 4)
	{
		line_env = ft_unset(line_env, data->cmd, in);
		return (ft_atoi(in.status));
	}
	else if (data->builtin_type == 5)
		line_env = ft_env(line_env, flag_one_pth);
	else if (data->builtin_type == 6)
	{
		in.status = ft_exit(data, in);
		line_env = ft_update_exp(line_env, flag_cd);
		return (ft_atoi(in.status));
	}
	line_env = ft_update_exp(line_env, flag_cd);
	flag_cd = 0;
	return (0);
}
