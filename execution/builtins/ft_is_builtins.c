/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/06/21 19:56:51 by akahir           ###   ########.fr       */
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
        return;
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
        return;
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
    int i;

    head = NULL;
    i = 0;
    while (env[i])
    {
        new_node = malloc(sizeof(t_built));
        if (!new_node)
            return (head);
        ft_take_var(new_node, i, env);
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
        i++;
    }
    return head;
}

void ft_is_builtins(t_data *data, char **env)
{
    static int flag_cd;
    static t_built *line_env;
    t_built *temp;

    if (!line_env)
        line_env = ft_fill_struct(env);
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
                break;
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
        line_env = ft_export(line_env, data->cmd, env, flag_cd);
    else if (data->builtin_type == 4)
        ft_unset(data->cmd, &env);
    else if (data->builtin_type == 5)
        ft_env(data->cmd, env);
    else if (data->builtin_type == 6)
        ft_exit(data->cmd);
    line_env = ft_update_exp(line_env, flag_cd);
    flag_cd = 0;
}
