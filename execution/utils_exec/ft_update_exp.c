/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/20 13:29:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_get_pwd_value(t_built *line)
{
    t_built *curr;
    
    curr = line;
    while (curr)
    {
        if (ft_strcmp(curr->var, "PWD") == 0)
        {
            if (curr->value)
                return (ft_strdup(curr->value));
            else
                return (NULL);
        }
        curr = curr->next;
    }
    return (NULL);
}

t_built *ft_update_exp(t_built *line, int flag_cd)
{
    t_built *curr;
    t_built *prev;
    t_built *temp;
    char *pwd;
    
    curr = line;
    prev = NULL;
    
    if (flag_cd == 1)
    {
        pwd = getcwd(NULL, 0);
        while (curr)
        {
            if (ft_strcmp(curr->var, "OLDPWD") == 0)
            {
                if (curr->value)
                    free(curr->value);
                curr->value = ft_get_pwd_value(line);
            }
            else if (ft_strcmp(curr->var, "PWD") == 0)
            {
                if (curr->value)
                    free(curr->value);
                curr->value = ft_strdup(pwd);
            }
            curr = curr->next;
        }
        if (pwd)
            free(pwd);
        curr = line;
        prev = NULL;
    }
    while (curr)
    {
        if (curr->var && 
            (ft_strncmp(curr->var, "./", 2) == 0 || 
             strstr(curr->var, ".out") != NULL ||
             strstr(curr->var, "/") != NULL))
        {
            temp = curr;
            if (prev)
                prev->next = curr->next;
            else
                line = curr->next;
            curr = curr->next;
            if (temp->var)
                free(temp->var);
            if (temp->value)
                free(temp->value);
            free(temp);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    return (line);
}
