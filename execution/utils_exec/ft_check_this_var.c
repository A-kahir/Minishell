/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_this_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:09:13 by akahir            #+#    #+#             */
/*   Updated: 2025/07/11 18:02:44 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_check_this_var(char *str, t_built *line_env)
{
	t_built *curr;
	int i;

	i = 0;
	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, str) == 0 && curr->value != NULL)
			return (0);
		curr = curr->next;
	}
	return (1);
}
