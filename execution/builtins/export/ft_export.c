/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/22 19:29:19 by akahir           ###   ########.fr       */
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
        int i;
        int flag_already = 0;
        int flag_dollar = 0;

        i = 0;
        while (cmd[i])
        {
            if (cmd[i][0] == '$')
            {
                flag_dollar = 1;
                t_built *curr;

                curr = line_env;
                while (curr)
                {
                    char *skip_dol = cmd[i] + 1;
                    if (ft_strcmp(skip_dol, curr->var) == 0)
                    {
                        if (curr->value == NULL)
                            ft_only_print(line_env);
                        else if (curr->value)
                        {
                            char *value = ft_strdup(curr->value);
                            t_built *check = line_env;
                            while (check)
                            {
                                if (ft_strcmp(check->var, value) == 0)
                                {
                                    flag_already = 1;
                                    break ;
                                }
                                check = check->next;
                            }
                            if (flag_already == 0)
                                line_env = ft_add_back(line_env, value, NULL);
                            else
                                free(value);
                            break;
                        }
                    }
                    curr = curr->next;
                }
            }
            i++;
        }
        if (flag_already == 0 && flag_dollar == 0)
            ft_add_vars(line_env, cmd);
    }
    return (line_env);
}
