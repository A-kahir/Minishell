/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 21:39:52 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void ft_only_print(t_built *line)
{
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
    t_built *line;
    
    line = line_env;
    line = ft_update_exp(line, flag_cd);
    line = ft_sort_vars(line);
    if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
        ft_only_print(line);
    else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL)
    {
        if (cmd[2] != NULL && cmd[3] == NULL)
        {
            line_env = ft_sort_by_order(line_env, cmd);
        }
        else if (cmd[2] == NULL)
        {
            char *tmp_cmd[] = {"export", cmd[1], "", NULL};
            line_env = ft_sort_by_order(line_env, tmp_cmd);
        }
    }
    return (line_env);
}
