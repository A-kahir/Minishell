/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:41 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 15:28:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_positif(t_built *line_env, char *cmd)
{
    t_built *curr;
    char **var;
    char *temp;
    char *skip_equal;

    var = ft_split(cmd, '+');
    if (!var || !var[0] || !var[1])
    {
        ft_free_split(var);
        return;
    }
    skip_equal = ft_strdup(var[1] + 1);
    curr = line_env;
    while (curr)
    {
        if (ft_strcmp(curr->var, var[0]) == 0)
        {
            if (curr->value)
                temp = ft_strjoin(curr->value, skip_equal);
            else
                temp = ft_strdup(skip_equal);
            free(curr->value);
            curr->value = temp;
            break ;
        }
        else if (ft_strcmp(curr->var, var[0]) != 0 && curr->next == NULL)
        {
            ft_add_back(line_env, var[0], skip_equal);
            break ;
        }
        curr = curr->next;
    }
    free(skip_equal);
    ft_free_split(var);
}
