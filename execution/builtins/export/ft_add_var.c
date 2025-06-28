/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:04 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 12:31:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void ft_add_var(t_built *line_env, char *cmd)
{
    char *equal;
    char *var;
    char *value;

    equal = ft_strchr(cmd, '=');
    var = NULL;
    value = NULL;
    if (equal)
    {
        int var_len = equal - cmd;
        var = ft_substr(cmd, 0, var_len);
        value = ft_strdup(equal + 1);
    }
    else
        var = ft_strdup(cmd);
    t_built *curr = line_env;
    int found = 0;
    while (curr)
    {
        if (ft_strcmp(curr->var, var) == 0)
        {
            found = 1;
            if (value)
            {
                free(curr->value);
                curr->value = ft_strdup(value);
            }
            break;
        }
        curr = curr->next;
    }
    if (!found)
        ft_add_back(line_env, var, value);

    free(var);
    if (value)
        free(value);
}

