/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:32:17 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 12:28:43 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_unset(t_built *line_env, char **cmd, char **env)
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
    if (access(cmd[i], F_OK) != 0)
	{
		return (line_env);
	}
	else if (access(cmd[i], X_OK) != 0)
	{
		return (line_env);
	}
    return (line_env);
}
