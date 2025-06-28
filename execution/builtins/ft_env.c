/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:25 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:11:07 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_env(t_built *line_env)
{
	t_built *curr;
	static int flag_path_env;
	
	if (line_env)
	{
		if (flag_path_env == 0)
			line_env = ft_add_back(line_env, "_", "/usr/bin/env");
		curr = line_env;
		while (curr)
		{
			if (ft_strcmp(curr->var, "PATH") == 0 && ft_strcmp(curr->next->var, "PWD") == 0 && ft_strcmp(curr->next->next->var, "SHLVL") == 0)
			{
				curr = curr->next;
				continue ;
			}
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
