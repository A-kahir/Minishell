/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:50 by akahir            #+#    #+#             */
/*   Updated: 2025/06/17 19:16:43 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_take_var(t_built *line_env, int i, char **env)
{
    char *line;
    int j = 0;
    int k;

    line = malloc(ft_strlen(env[i]) + 1);
    if (!line)
        return;
    while (env[i][j])
    {
        line[j] = env[i][j];
        j++;
    }
    line[j] = '\0';
    j = 0;
    while (line[j] != '=' && line[j] != '\0')
        j++;
    line_env->var = malloc(j + 1);
    if (!line_env->var)
        return;
    k = 0;
    while (k < j)
    {
        line_env->var[k] = line[k];
        k++;
    }
    line_env->var[k] = '\0';
    if (line[j] == '=')
        j++;
    line_env->value = malloc(ft_strlen(&line[j]) + 1);
    if (!line_env->value)
        return;
    k = 0;
    while (line[j])
    {
        line_env->value[k] = line[j];
        j++;
        k++;
    }
    line_env->value[k] = '\0';
    free(line);
}

void ft_fill_struct(char **env)
{
    t_built *line_env;
    int i;

    line_env = malloc(sizeof(t_built));
    if (!line_env)
        return;
    i = 0;
    while (env[i] != NULL)
    {
        ft_take_var(line_env, i, env);
        free(line_env->var);
        free(line_env->value);
        i++;
    }
    free(line_env);
}

void ft_is_builtins(t_data *data, char **env)
{
    
    ft_fill_struct(env);
    if (data->builtin_type == 0)
    {
        ft_echo(data->cmd);
    }
    else if (data->builtin_type == 1)
    {
        ft_cd(data->cmd);
    }
    else if (data->builtin_type == 2)
    {
        ft_pwd(data->cmd);
    }
    else if (data->builtin_type == 3)
    {
        //soon
    }
    else if (data->builtin_type == 4)
    {
        //need fix allocation
        ft_unset(data->cmd, &env);
    }
    else if (data->builtin_type == 5)
    {
        ft_env(data->cmd, env);
    }
    else if (data->builtin_type == 6)
    {
        ft_exit(data->cmd);
    }
}
