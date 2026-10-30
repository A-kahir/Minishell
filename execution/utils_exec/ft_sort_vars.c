/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:30:14 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 22:40:13 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_swp_vars(t_built *a, t_built *b)
{
	char	*tmp_var;
	char	*tmp_value;

	tmp_var = a->var;
	tmp_value = a->value;
	a->var = b->var;
	a->value = b->value;
	b->var = tmp_var;
	b->value = tmp_value;
}

t_built	*ft_sort_vars(t_built *head_node)
{
	t_built	*a;
	t_built	*b;

	if (!head_node || !head_node->next)
		return (head_node);
	a = head_node;
	while (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if (ft_strcmp(a->var, b->var) > 0)
				ft_swp_vars(a, b);
			b = b->next;
		}
		a = a->next;
	}
	return (head_node);
}
