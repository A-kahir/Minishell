/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:11:40 by akahir            #+#    #+#             */
/*   Updated: 2025/05/28 13:18:53 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


char *ft_check_built_redir(t_data *data, int flag)
{
    char *str;

    if (flag == 0)
    {
        if (ft_strcmp(data->cmd[0], "echo") == 0)
            return (str = "echo");
        else if (ft_strcmp(data->cmd[0], "cd") == 0)
            return (str = "cd");
        else if (ft_strcmp(data->cmd[0], "env") == 0)
            return (str = "env");
        else if (ft_strcmp(data->cmd[0], "exit") == 0)
            return (str = "exit");
        else if (ft_strcmp(data->cmd[0], "export") == 0)
            return (str = "export");
        else if (ft_strcmp(data->cmd[0], "pwd") == 0)
            return (str = "pwd");
        else if (ft_strcmp(data->cmd[0], "unset") == 0)
            return (str = "unset");
    }
    else if (flag == 1)
    {
        if (ft_strcmp(data->cmd[0], "<") == 0)
            return (str = "<");
        else if (ft_strcmp(data->cmd[0], "<<") == 0)
            return (str = "<<");
        else if (ft_strcmp(data->cmd[0], ">") == 0)
            return (str = ">");
        else if (ft_strcmp(data->cmd[0], ">>") == 0)
            return (str = ">>");
    }
    return (NULL);
}