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

int	ft_is_builtins_f(t_data *data, t_built *line_env, t_exec in)
{
	static int	flag_cd;

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
		line_env = ft_export(line_env, data->cmd);
	else if (data->builtin_type == 4)
		line_env = ft_unset(line_env, data->cmd);
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
