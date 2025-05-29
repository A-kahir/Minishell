/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_built_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:11:40 by akahir            #+#    #+#             */
/*   Updated: 2025/05/29 13:51:25 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_check_built_redir(t_data *data, char **env)
{
    char *str;

    str = "redir";
    if ((!data->redir || data->redir->type == -1) && (ft_strcmp(data->cmd[0], "echo") == 0 || ft_strcmp(data->cmd[0], "cd") == 0
        || ft_strcmp(data->cmd[0], "env") == 0 || ft_strcmp(data->cmd[0], "exit") == 0
        || ft_strcmp(data->cmd[0], "export") == 0 || ft_strcmp(data->cmd[0], "pwd") == 0
        || ft_strcmp(data->cmd[0], "unset") == 0))
        {
           str = "built";
        }
    else if ((!data->redir || data->redir->type == -1))
    {
        char **cmd = ft_get_path(data->cmd[0], env);
        str = "cmd";    
    }
    return (str);
}
