/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/05/24 16:21:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_builtins(t_data *data, char **env)
{
    if (data->builtin_type == 0)
    {
        ft_echo(data->cmd);
    }
    else if (data->builtin_type == 1)
    {
        ft_cd(data->cmd);
    }
    else if (data->builtin_type == 2)
    {
        ft_pwd(data->cmd);
    }
    else if (data->builtin_type == 3)
    {
        //soon
    }
    else if (data->builtin_type == 4)
    {
        //need fix allocation
        ft_unset(data->cmd, &env);
    }
    else if (data->builtin_type == 5)
    {
        ft_env(data->cmd, env);
    }
    else if (data->builtin_type == 6)
    {
        ft_exit(data->cmd);
    }
}
