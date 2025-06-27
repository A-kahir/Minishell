/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 16:30:01 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void ft_only_print(t_built *line)
{
    t_built *curr;

    curr = line;
    curr = ft_sort_vars(curr);
    while (curr)
    {
        if (ft_strcmp(curr->var, "PATH") == 0 && ft_strcmp(curr->next->var, "PWD") == 0 && ft_strcmp(curr->next->next->var, "SHLVL") == 0)
        {
            curr = curr->next;
            continue ;
        }
        if (ft_strcmp(curr->var, "_") == 0 && curr->value && ft_strcmp(curr->value, "/usr/bin/env") == 0)
        {
            curr = curr->next;
            continue ;
        }
        if (curr->var)
        {
            write(1, "declare -x ", 12);
            printf("%s", curr->var);
            if (curr->value)
                printf("=\"%s\"", curr->value);
            printf("\n");
        }
        curr = curr->next;
    }
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
            int check = ft_specify_var(cmd[i]);
            if (cmd[i][0] == '$')
                ft_only_print(line_env);
            else if (check == 1)
                ft_is_positif(line_env, cmd[i]);
            else if (check == -1)
            {
                printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
                return (line_env);
            }
            else if (check == 0)
               ft_add_vars(line_env, cmd);
            i++;
        }
    }
    return (line_env);
}
