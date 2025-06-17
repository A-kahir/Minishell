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

void ft_take_var(t_built *line_env,int i, char **env)
{
    char *line;
    int j;

    j = 0;
    line = malloc(ft_strlen(&env[i][j]) + 1);
    if (!line)
        return ;
    j = 0;
    while (env[i][j] != '\0')
    {
        line[j] = env[i][j];
        j++;
    }
    line[j] = '\0';
    j = 0;
    while (line[j] != '=')
    {
        j++;
    }
    line_env->var = malloc(j + 1);
    if (!line_env->var)
        return ;
    j = 0;
    while (line[j] != '=')
    {
        line_env->var[j] = line[j];
        j++;
    }
    line_env->var[j] = '\0';
}

void ft_fill_struct(char **env)
{
    t_built *line_env;
    char *line;
    int i;
    int j;

    line_env = malloc(sizeof(t_built));
    if (!line_env)
        return ;
    i = 0;
    while (env[i] != NULL)
    {
        ft_take_var(line_env, i, env);
        printf("VAR => %s\n", line_env->var + 1);

        
        int len_val = ft_strlen(line_env->var);
        while (line[len_val] != '=')
            len_val++;
        if (line[len_val] == '=')
            len_val++;
        printf("leeeeen => %d\n", len_val);        
        // printf("VALUE => %s\n", line_env->value);
        i++;
    }
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
