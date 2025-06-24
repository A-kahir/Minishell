/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/06/24 18:42:53 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_builtins(t_data *data, t_built *line_env)
{
    static int flag_cd;
    t_built *temp;

    if (data->builtin_type == 3)
    {
        temp = line_env;
        while (temp)
        {
            if (ft_strcmp(temp->var, "PWD") == 0)
            {
                if (line_env->old_pwd)
                {
                    free(line_env->old_pwd);
                    line_env->old_pwd = NULL;
                }
                if (temp->value)
                    line_env->old_pwd = ft_strdup(temp->value);
                break ;
            }
            temp = temp->next;
        }
    }
    if (data->builtin_type == 0)
        ft_echo(data->cmd);
    else if (data->builtin_type == 1)
    {
        ft_cd(data->cmd);
        flag_cd = 1;
    }
    else if (data->builtin_type == 2)
        ft_pwd(data->cmd);
    else if (data->builtin_type == 3)
        line_env = ft_export(line_env, data->cmd, flag_cd);
    else if (data->builtin_type == 4)
        line_env = ft_unset(line_env, data->cmd);
    else if (data->builtin_type == 5)
        line_env = ft_env(line_env);
    else if (data->builtin_type == 6)
        ft_exit(data->cmd);
    line_env = ft_update_exp(line_env, flag_cd);
    flag_cd = 0;
}
