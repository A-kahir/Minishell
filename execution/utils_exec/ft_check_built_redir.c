/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_built_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:11:40 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 12:54:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_check_built_redir(t_data *data, char **env)
{
    char *str;

    if (data->redir && data->redir->type != -1)
        str = "redir";
    else if (ft_strcmp(data->cmd[0], "echo") == 0 || ft_strcmp(data->cmd[0], "cd") == 0
        || ft_strcmp(data->cmd[0], "env") == 0 || ft_strcmp(data->cmd[0], "exit") == 0
        || ft_strcmp(data->cmd[0], "export") == 0 || ft_strcmp(data->cmd[0], "pwd") == 0
        || ft_strcmp(data->cmd[0], "unset") == 0)
        str = "built";
    else
        str = "cmd";
    return (str);
}

