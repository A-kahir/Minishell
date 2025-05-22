/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:58 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 16:30:20 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_is_numeric(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void ft_exit(char **str)
{
    int i;
    long exit_code; // i want to test if i change them to unsigned long;

    i = 0;
    exit_code = 0;
    if (!str[i] || ft_strcmp(str[i], "exit") != 0)
        return;
    printf("exit\n");
    if (str[i + 1] && str[i + 2])
    {
        printf("minishell: exit: too many arguments\n");
        return;
    }
    if (str[i + 1])
    {
        if (!ft_is_numeric(str[i + 1]))
        {
            printf("minishell: exit: %s: numeric argument required\n", str[i + 1]);
            exit(1);
        }
        exit_code = ft_atoi(str[i + 1]);
        exit(exit_code);
    }
    exit(0);
}
