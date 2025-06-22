/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/22 19:18:02 by akahir           ###   ########.fr       */
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

t_built *ft_export(t_built *line_env, char **cmd, char **env, int flag_cd)
{
    if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
        ft_only_print(line_env);
    else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL)
    {
        int i = 1;
        while (cmd[i])
        {
            char *equal_sign = ft_strchr(cmd[i], '=');
            char *var = NULL;
            char *val = NULL;

            if (equal_sign)
            {
                int var_len = equal_sign - cmd[i];
                var = ft_substr(cmd[i], 0, var_len);
                val = ft_strdup(equal_sign + 1);
            }
            else
            {
                var = ft_strdup(cmd[i]);
                val = NULL;
            }
            t_built *curr = line_env;
            int found = 0;
            while (curr)
            {
                if (ft_strcmp(curr->var, var) == 0)
                {
                    found = 1;
                    if (val != NULL)
                    {
                        free(curr->value);
                        curr->value = ft_strdup(val);
                    }
                    break;
                }
                curr = curr->next;
            }
            if (!found)
            {
                line_env = ft_add_back(line_env, var, val);
            }
            free(var);
            if (val)
                free(val);
            i++;
        }
    }
    return (line_env);
}
