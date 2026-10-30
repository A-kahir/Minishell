/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:58 by akahir            #+#    #+#             */
/*   Updated: 2025/08/04 12:48:03 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static char	*ft_exit_exec(t_data *data, t_exec *in, int arg_count)
{
	unsigned long	exit_code;

	write(1, "exit\n", 5);
	if (arg_count >= 2 && !ft_is_numeric(data->cmd[1]))
	{
		write(2, "minishell: exit: ", 18);
		write(2, data->cmd[1], ft_strlen(data->cmd[1]));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	if (arg_count > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		in->status = ft_strdup("1", 0, 0);
		return (in->status);
	}
	if (arg_count == 2)
	{
		exit_code = ft_atoi(data->cmd[1]);
		exit((unsigned char)(exit_code % 256));
	}
	exit_code = ft_atoi(in->status);
	exit((unsigned char)(exit_code % 256));
}

char	*ft_exit(t_data *data, t_exec *in)
{
	int	arg_count;

	arg_count = 0;
	while (data->cmd[arg_count])
		arg_count++;
	if (in->n_cmds > 1)
	{
		if (arg_count >= 2 && !ft_is_numeric(data->cmd[1]))
		{
			write(2, "minishell: exit: ", 18);
			write(2, data->cmd[1], ft_strlen(data->cmd[1]));
			write(2, ": numeric argument required\n", 29);
			return (ft_strdup("255", 0, 0));
		}
		if (arg_count > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (ft_strdup("1", 0, 0));
		}
		if (arg_count == 2)
			return (ft_strdup(data->cmd[1], 0, 0));
		return (ft_strdup("0", 0, 0));
	}
	return (ft_exit_exec(data, in, arg_count));
}
