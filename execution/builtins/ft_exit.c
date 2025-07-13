/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:58 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:58:27 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int is_numeric(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_is_digit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static char *update_status(char *old_status, char *new_status)
{
	if (old_status)
		free(old_status);
	return (ft_strdup(new_status));
}

char *ft_exit(t_data *data, t_exec in)
{
    int arg_count = 0;
    unsigned long exit_code;

    while (data->cmd[arg_count])
        arg_count++;
    if (ft_strcmp(data->cmd[0], "exit") != 0)
        return (ft_strdup(in.status));
    if (in.n_cmds > 1)
    {
        if (arg_count > 2)
        {
            write(2, "minishell: exit: too many arguments\n", 36);
            return (ft_strdup("1"));
        }
        if (arg_count == 2)
        {
			printf("*****************\n");
            if (!is_numeric(data->cmd[1]))
            {
                write(2, "minishell: exit: ", 17);
                write(2, data->cmd[1], ft_strlen(data->cmd[1]));
                write(2, ": numeric argument required\n", 27);
                return (ft_strdup("2"));
            }
            return (ft_strdup(data->cmd[1]));
        }
        return (ft_strdup(in.status));
    }
    write(1, "exit\n", 5);
    if (arg_count > 2)
    {
        write(2, "minishell: exit: too many arguments\n", 36);
        return (ft_strdup("1"));
    }
    if (arg_count == 2)
    {
        if (!is_numeric(data->cmd[1]))
        {
            write(2, "minishell: exit: ", 17);
            write(2, data->cmd[1], ft_strlen(data->cmd[1]));
            write(2, ": numeric argument required\n", 27);
            exit(2);
        }
        exit_code = ft_atoi(data->cmd[1]);
        exit_code %= 256;
        exit((unsigned char)exit_code);
    }
    exit_code = ft_atoi(in.status);
    exit_code %= 256;
    exit((unsigned char)exit_code);
    return (NULL);
}
