/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:09:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int ft_add_vars(char **cmd)
{
    int i = 1;
    int count = 0;

    while (cmd[i])
    {
        if (cmd[i][0] == '$' && ft_strlen(cmd[i]) == 1)
        {
            i++;
            continue;
        }
        if (cmd[i][0] == '$' && getenv(cmd[i] + 1) == NULL)
        {
            i++;
            continue;
        }
        count++;
        i++;
    }
    return count;
}

t_built *ft_export(t_built *line_env, char **cmd)
{
    if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
        ft_only_print(line_env);
    else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL)
    {
        int i = 1;
        int print_export = 0;
        int valid_count = ft_add_vars(cmd);

        if (valid_count == 0)
        {
            ft_only_print(line_env);
            return line_env;
        }
        while (cmd[i])
        {
            char *buff = getenv(cmd[i] + 1);
            if (cmd[i][0] == '$' && buff == NULL)
            {
                i++;
                continue;
            }
            int check = ft_specify_var(cmd[i]);
            if (check == 4)
            {
                print_export = 1;
                i++;
                continue;
            }
            if (check == 1)
            {
                ft_is_positif(line_env, cmd[i]);
                print_export = 0;
            }
            else if (check == -1)
            {
                printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
                return line_env;
            }
            else if (check == 0)
            {
                ft_add_var(line_env, cmd[i]);
                print_export = 0;
            }
            i++;
        }
        if (print_export)
            ft_only_print(line_env);
    }
    return (line_env);
}
