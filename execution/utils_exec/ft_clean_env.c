/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:03:31 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 19:04:28 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_clean_env(t_built **line_env_ptr)
{
	t_built	*curr;
	t_built	*tmp;

	curr = *line_env_ptr;
	while (curr)
	{
		tmp = curr->next;
		if (ft_strcmp(curr->var, "PWD") != 0
			&& ft_strcmp(curr->var, "SHLVL") != 0
			&& ft_strcmp(curr->var, "OLDPWD") != 0)
		{
			if (curr->var && ft_strcmp(curr->var, "PATH") == 0)
			{
				if (curr->value)
					curr->value = NULL;
				curr->value = ft_strdup(PATH_ENV, 0, 1);
			}
			else
				ft_rm_list_env(line_env_ptr, curr);
		}
		curr = tmp;
	}
}
