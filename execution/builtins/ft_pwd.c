/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:31:45 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:22:44 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_pwd(t_built *line_env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
	{
		t_built *curr = line_env;
		while (curr)
		{
			if (ft_strcmp(curr->var, "PWD") == 0)
			{
				printf("%s\n", curr->value);
				break ;
			}
			curr = curr->next;
		}
	}
}
