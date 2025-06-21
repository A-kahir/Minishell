/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/21 20:21:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_update_exp(t_built *line, int flag_cd)
{
    t_built *curr;
    int have_old_pwd;

    curr = line;
    have_old_pwd = 0;
    while (curr)
    {
        if (ft_strcmp(curr->var, "OLDPWD") == 0)
        {
            have_old_pwd = 1;
            if (flag_cd == 1 && line->old_pwd)
            {
                if (curr->value)
                {
                    free(curr->value);
                    curr->value = NULL;
                }
                curr->value = ft_strdup(line->old_pwd);
            }
            break ;
        }
        curr = curr->next;
    }
    if (!have_old_pwd)
        line = ft_add_front(line, "OLDPWD", NULL);
    if (flag_cd == 1)
    {
        curr = line;
        while (curr)
        {
            if (ft_strcmp(curr->var, "PWD") == 0)
            {
                char *buff = getcwd(NULL, 0);
                if (buff)
                {
                    if (curr->value)
                    {
                        free(curr->value);
                        curr->value = NULL;
                    }
                    curr->value = ft_strdup(buff);
                    free(buff);
                }
                break ;
            }
            curr = curr->next;
        }
    }
    return (line);
}
