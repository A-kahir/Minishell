/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:57:59 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:30:05 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_save_oldpwd_f(t_built *temp, char *before_cd)
{
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
		{
			if (temp->value)
				free(temp->value);
			temp->value = before_cd;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static t_built	*ft_handle_cd(t_data *data, t_built *line_env, int *flag_cd)
{
	t_built	*temp;
	char	*before_cd;

	before_cd = NULL;
	temp = line_env;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
		{
			if (temp->value)
				before_cd = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	line_env = ft_cd(data->cmd, line_env);
	*flag_cd = 1;
	temp = line_env;
	if (!ft_save_oldpwd_f(temp, before_cd) && before_cd)
		line_env = ft_add_front(line_env, "OLDPWD", before_cd);
	return (line_env);
}

void	ft_is_builtins_f(t_data *data, t_built *line_env, t_exec in)
{
	static int	flag_cd;

	if (data->builtin_type == 1)
		line_env = ft_handle_cd(data, line_env, &flag_cd);
	else if (data->builtin_type == 0)
		ft_echo(data->cmd, in);
	else if (data->builtin_type == 2)
		ft_pwd();
	else if (data->builtin_type == 3)
		line_env = ft_export(line_env, data->cmd);
	else if (data->builtin_type == 4)
		line_env = ft_unset(line_env, data->cmd);
	else if (data->builtin_type == 6)
		ft_exit(data->cmd);
	line_env = ft_update_exp(line_env, flag_cd);
	flag_cd = 0;
}
