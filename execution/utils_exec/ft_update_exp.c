/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 19:21:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_update_exp(t_built *line, int flag)
{
    t_built *curr;
    
    curr = line;
    while (curr)
    {
        if (curr->value && ft_strcmp(curr->value, "./a.out") == 0)
            ft_rm_list(&line, curr);
        else if (flag == 0 && ft_strcmp(curr->var, "OLDPWD") == 0)
        {
            free(curr->value);
            curr->value = NULL;
        }
        if (flag == 1 && ft_strcmp(curr->var, "OLDPWD") == 0)
        {
            char *buff;
            buff = getcwd(NULL, 0);
            free(curr->value);
            curr->value = NULL;
            curr->value = ft_strdup(buff);
        }
        curr = curr->next;
    }
    return (line);
}
