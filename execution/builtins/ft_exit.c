/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:58 by akahir            #+#    #+#             */
/*   Updated: 2025/07/15 18:16:48 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}
int is_numeric(const char *str)
{
	int i = 0;
	int digit = 0;
	int sign = 1;
	unsigned long long result = 0;
	unsigned long long max = 9223372036854775807ULL;

	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		digit = 1;
		if (result > (max - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (!digit)
		return (0);
	return (1);
}

static char *update_status(char *old_status, char *new_status)
{
	if (old_status)
		free(old_status);
	return (ft_strdup(new_status));
}

char *ft_exit(t_data *data, t_exec *in)
{
	int arg_count = 0;
	unsigned long exit_code;

	while (data->cmd[arg_count])
		arg_count++;
	if (ft_strcmp(data->cmd[0], "exit") != 0)
		return (ft_strdup(in->status));
	if (in->n_cmds > 1)
	{
		if (arg_count >= 2 && !is_numeric(data->cmd[1]))
		{
			write(2, "minishell: exit: ", 18);
			write(2, data->cmd[1], ft_strlen(data->cmd[1]));
			write(2, ": numeric argument required\n", 29);
			in->status = ft_strdup("255");
			return (in->status);
		}
		if (arg_count > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (ft_strdup("1"));
		}
		if (arg_count == 2)
			return (ft_strdup(data->cmd[1]));
		in->status = ft_strdup("0");
		return (in->status);
	}
	write(1, "exit\n", 5);
	if (arg_count >= 2 && !is_numeric(data->cmd[1]))
	{
		write(2, "minishell: exit: ", 18);
		write(2, data->cmd[1], ft_strlen(data->cmd[1]));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	if (arg_count > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (ft_strdup("1"));
	}
	if (arg_count == 2)
	{
		exit_code = ft_atoi(data->cmd[1]);
		exit_code %= 256;
		exit((unsigned char)exit_code);
	}
	exit_code = ft_atoi(in->status);
	exit_code %= 256;
	exit((unsigned char)exit_code);
	return (NULL);
}
