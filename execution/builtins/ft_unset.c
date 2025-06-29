/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:32:17 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:37:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_unset(t_built *line_env, char **cmd)
{
	t_built	*curr;
	int		i;

	i = 1;
	while (cmd[i])
	{
		curr = line_env;
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
