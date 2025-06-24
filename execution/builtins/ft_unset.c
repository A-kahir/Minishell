/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:32:17 by akahir            #+#    #+#             */
/*   Updated: 2025/06/24 18:54:19 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_unset(t_built *line_env, char **cmd)
{
    t_built *curr;
    int i;
 
    curr = line_env;
    i = 1;
    while (cmd[i])
    {
        while (curr)
        {
            if (ft_strcmp(curr->var, cmd[i]) == 0)
            {
                ft_rm_list(&line_env, curr);
                break ;
            }
            curr = curr->next;
        }
        i++;
    }
    return (line_env);
}
