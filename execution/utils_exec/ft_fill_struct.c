/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:23:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 22:47:52 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_take_value(t_built *line_env, char *env_line, int start)
{
    int len;
    int k;

    k = 0;
    if (env_line[start] == '=')
        start++;
    len = ft_strlen(&env_line[start]);
    line_env->value = malloc(len + 1);
    if (!line_env->value)
        return ;
    while (env_line[start])
    {
        line_env->value[k] = env_line[start];
        k++;
        start++;
    }
    line_env->value[k] = '\0';
}

void ft_take_var(t_built *line_env, int i, char **env)
{
    int j;
    int k;

    j = 0;
    while (env[i][j] != '=' && env[i][j] != '\0')
        j++;
    line_env->var = malloc(j + 1);
    if (!line_env->var)
        return ;
    k = 0;
    while (k < j)
    {
        line_env->var[k] = env[i][k];
        k++;
    }
    line_env->var[k] = '\0';
    if (ft_strcmp(line_env->var, "OLDPWD") == 0)
        line_env->value = NULL;
    else
        ft_take_value(line_env, env[i], j);
}

t_built *ft_fill_struct(char **env)
{
    t_built *head;
    t_built *new_node;
    t_built *last;
    t_built *temp;
    int i;

    head = NULL;
    i = 0;
    while (env[i])
    {
        new_node = malloc(sizeof(t_built));
        if (!new_node)
            return (head);
        memset(new_node, 0, sizeof(t_built));
        ft_take_var(new_node, i, env);
        if (new_node->value && ft_strcmp(new_node->value, "./a.out") == 0)
            (free(new_node->var), free(new_node->value), free(new_node));
        else
        {
            new_node->old_pwd = NULL;
            new_node->next = NULL;
            if (!head)
                head = new_node;
            else
            {
                last = head;
                while (last->next)
                    last = last->next;
                last->next = new_node;
            }
        }
        i++;
    }
    temp = head;
    while (temp)
    {
        t_built *next = temp->next;
        if (temp->value && ft_strcmp(temp->value, "./a.out") == 0)
            ft_rm_list(&head, temp);
        temp = next;
    }
    return (head);
}
