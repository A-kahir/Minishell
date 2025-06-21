/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/21 16:46:44 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
t_built *ft_update_exp(t_built *line, int flag_cd)
{
    t_built *curr;
    t_built *temp;
    char *old_pwd;
    
    old_pwd = NULL;
    if (flag_cd == 1)
    {
        curr = line;
        while (curr)
        {
            if (ft_strcmp(curr->var, "PWD") == 0)
            {
                old_pwd = ft_strdup(curr->value);
                break;
            }
            curr = curr->next;
        }
    }
    curr = line;
    while (curr)
    {
        if (curr->value && ft_strcmp(curr->value, "./a.out") == 0)
            ft_rm_list(&line, curr);
        if (flag_cd == 0 && ft_strcmp(curr->var, "OLDPWD") == 0)
        {
            free(curr->value);
            curr->value = NULL;
        }
        if (flag_cd == 1 && ft_strcmp(curr->var, "OLDPWD") == 0)
        {
            free(curr->value);
            curr->value = ft_strdup(old_pwd);
        }
        if (flag_cd == 1 && ft_strcmp(curr->var, "PWD") == 0)
        {
            char *buff;
            buff = getcwd(NULL, 0);
            free(curr->value);
            curr->value = NULL;
            curr->value = ft_strdup(buff);
            free(buff);
        }
        curr = curr->next;
    }
    if (old_pwd)
        free(old_pwd);
    return (line);
}
