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


void ft_add_vars(t_built *line_env, char **cmd)
{
    char *equal;
    char *var;
    char *value;
    int i;
    
    i = 1;
    while (cmd[i])
    {
        equal = ft_strchr(cmd[i], '=');
        var = NULL;
        value = NULL;
        if (equal)
        {
            int var_len = equal - cmd[i];
            var = ft_substr(cmd[i], 0, var_len);
            value = ft_strdup(equal + 1);
        }
        else
        {
            var = ft_strdup(cmd[i]);
            value = NULL;
        }
        t_built *curr = line_env;
        int found = 0;
        while (curr)
        {
            if (ft_strcmp(curr->var, var) == 0)
            {
                found = 1;
                if (value != NULL)
                {
                    free(curr->value);
                    curr->value = ft_strdup(value);
                }
                break;
            }
            curr = curr->next;
        }
        if (!found)
        {
            line_env = ft_add_back(line_env, var, value);
        }
        free(var);
        if (value)
            free(value);
        i++;
    }
}
