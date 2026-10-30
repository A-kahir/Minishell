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

static int	ft_is_cd(t_data *data, t_built **line_env, int *flag_cd, t_exec *in)
{
	*line_env = ft_handle_cd(data, *line_env, flag_cd, in);
	*line_env = ft_update_exp(*line_env, *flag_cd);
	return (ft_atoi(in->status));
}

static int	ft_handle_pwd_case(t_built **line_env, int flag_cd, t_exec *in)
{
	in->status = ft_pwd(*line_env);
	*line_env = ft_update_exp(*line_env, flag_cd);
	return (ft_atoi(in->status));
}

static int	ft_is_export(t_data *data, t_built **line_env,
int flag_one_pth, t_exec *in)
{
	if (ft_strcmp(data->cmd[0], "export") == 0 && data->cmd[1] == NULL)
	{
		ft_only_print(*line_env, flag_one_pth);
		in->status = ft_strdup("0", 0, 0);
		return (ft_atoi(in->status));
	}
	*line_env = ft_export(*line_env, data->cmd, flag_one_pth, in);
	return (ft_atoi(in->status));
}

int	ft_cantinue_builin_f(t_data *data, t_built *line_env,
	t_exec in, int *flag_cd)
{
	if (data->builtin_type == 4)
	{
		line_env = ft_unset(line_env, data->cmd, &in);
		line_env = ft_update_exp(line_env, *flag_cd);
		return (ft_atoi(in.status));
	}
	else if (data->builtin_type == 6)
	{
		in.status = ft_exit(data, &in);
		line_env = ft_update_exp(line_env, *flag_cd);
		return (ft_atoi(in.status));
	}
	1 && (line_env = ft_update_exp(line_env, *flag_cd), *flag_cd = 0);
	return (0);
}

int	ft_is_builtins_f(t_data *data, t_built *line_env, t_exec in)
{
	static int	flag_cd;
	static int	flag_one_pth;

	if (!data)
		return (0);
	ft_check_path_var(data, line_env, &flag_one_pth);
	if (data->builtin_type == 1)
		return (ft_is_cd(data, &line_env, &flag_cd, &in));
	else if (data->builtin_type == 0)
		ft_echo(data->cmd);
	else if (data->builtin_type == 2)
		return (ft_handle_pwd_case(&line_env, flag_cd, &in));
	else if (data->builtin_type == 3)
		return (ft_is_export(data, &line_env, flag_one_pth, &in));
	return (ft_cantinue_builin_f(data, line_env, in, &flag_cd));
}
