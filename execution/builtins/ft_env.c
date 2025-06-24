/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:25 by akahir            #+#    #+#             */
/*   Updated: 2025/06/24 20:23:41 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_env(t_built *line_env)
{
	t_built *curr;
	int	i;
	
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
	printf("_=/usr/bin/env\n");
	return (line_env);
}
