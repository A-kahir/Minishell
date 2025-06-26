/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:25 by akahir            #+#    #+#             */
/*   Updated: 2025/06/26 14:43:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_env(t_built *line_env)
{
	t_built *curr;
	static int flag_path_env;
	int	i;
	
	if (line_env)
	{
		if (flag_path_env == 0)
			line_env = ft_add_back(line_env, "_", "/usr/bin/env");
		curr = line_env;
		while (curr)
		{
			if (curr->var && curr->value)
			{
				printf("%s=", curr->var);
				printf("%s\n", curr->value);
			}
			curr = curr->next;
		}
		flag_path_env = 1;
	}
	return (line_env);
}
