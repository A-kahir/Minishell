/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_un_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:04:31 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:04:31 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_type_1(t_data **data, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	char	*command;
	int		status;
	int		flag_redir;

	1 && (flag_redir = ft_flag_redir(*data), status = 0);
	command = ft_check_built_redir(*data);
	if (command && ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
	{
		status = ft_exec_cmd_1(data, line_env, env_here, in);
	}
	if (*data && ((command && ft_strcmp(command, "cmd") == 0
				&& flag_redir == 0) || (*data)->builtin_type == 5))
	{
		write(2, "minishell: ", 12);
		write(2, (*data)->cmd[0], ft_strlen((*data)->cmd[0]));
		write(2, ": No such file or directory\n", 29);
		return (127);
	}
	if (command && ft_strcmp(command, "built") == 0
		&& (*data)->builtin_type != -1 && (*data)->builtin_type != 5)
		status = ft_is_builtins_f(*data, line_env, *in);
	return (status);
}

static int	ft_handle_redirection(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec stat)
{
	int	status;

	status = 0;
	if (ft_flag_redir(data) == 1)
		status = ft_is_redir(data, line_env, env_here, stat);
	return (status);
}

int	ft_if_un_path(t_data *data, t_ex_othr env_here,
t_built *line_env, t_exec stat)
{
	t_exec			in;
	int				flag_redir;
	int				init_result;
	int				status;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	status = 0;
	in.status = ft_strdup(stat.status, 0, 0);
	1 && (flag_redir = ft_flag_redir(data), init_result = ft_in_pp(&in, data));
	if (init_result != 1)
		return (init_result);
	if (data->type == 0 && flag_redir == 0)
	{
		return (ft_type_0(&data, line_env, env_here, &in));
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		status = ft_type_1(&data, line_env, env_here, &in);
		if (status == 127)
			return (status);
		if (flag_redir == 1)
			status = ft_handle_redirection(data, line_env, env_here, stat);
	}
	return (status);
}
