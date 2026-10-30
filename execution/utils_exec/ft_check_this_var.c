/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_this_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:09:13 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 18:57:48 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_check_this_var(char *str, t_built *line_env)
{
	t_built	*curr;

	curr = line_env;
	while (curr)
	{
		if (!str || str[0] == '\0' || !line_env)
			return (1);
		if (str && curr->var && ft_strcmp(curr->var, str) == 0 && curr->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}
