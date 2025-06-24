/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/24 18:02:57 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void ft_only_print(t_built *line)
{
    line = ft_sort_vars(line);
    while (line)
    {
        write(1, "declare -x ", 12);
        printf("%s", line->var);
        if (line->value != NULL)
        {
            printf("=");
            printf("\"%s\"", line->value);
        }
        printf("\n");
        line = line->next;
    }
}

int ft_cantinue(t_built *line_env, char **cmd, int i)
{
    char *plus;
    char *equal;
    
    plus = ft_strchr(cmd[i], '+');
    equal = ft_strchr(cmd[i], '=');
    if (plus && equal && (plus + 1 == equal))
    {
        ft_is_positif(line_env, cmd[i]);
        return (1);
    }
    else if (((ft_strchr(cmd[i], '-') || ft_strchr(cmd[i], '*') || plus + 1 != equal)) && equal)
    {
        printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
        return (0);
    }
    return (1);
}

t_built *ft_export(t_built *line_env, char **cmd, int flag_cd)
{
    if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
        ft_only_print(line_env);
    else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL)
    {
        int i;

        i = 1;
        while (cmd[i])
        {
            if (cmd[i][0] == '$')
                ft_only_print(line_env);
            else if (ft_pos_neg(cmd[i]) == 0)
            {
                if (ft_cantinue(line_env, cmd, i) == 0)
                    break ;
            }
            else
            {
               ft_add_vars(line_env, cmd);
            }
            i++;
        }
    }
    return (line_env);
}
