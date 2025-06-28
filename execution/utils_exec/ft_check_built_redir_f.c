/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_built_redir_f.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:03:36 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:27:15 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_check_built_redir_f(t_data *data)
{
    char *str;

    if (data->redir && data->redir->type != -1)
        str = "redir";
    else if (ft_strcmp(data->cmd[0], "echo") == 0 || ft_strcmp(data->cmd[0], "cd") == 0
        || ft_strcmp(data->cmd[0], "exit") == 0
        || ft_strcmp(data->cmd[0], "export") == 0 || ft_strcmp(data->cmd[0], "pwd") == 0
        || ft_strcmp(data->cmd[0], "unset") == 0)
        str = "built";
    else
        str = "cmd";
    return (str);
}
