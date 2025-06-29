/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:30:14 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 16:24:40 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_swap_var(t_built *a, t_built *b)
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

t_built	*ft_sort_vars(t_built *head)
{
	t_built	*a;
	t_built	*b;

	if (!head || !head->next)
		return (head);
	a = head;
	while (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if (ft_strcmp(a->var, b->var) > 0)
				ft_swap_var(a, b);
			b = b->next;
		}
		a = a->next;
	}
	return (head);
}
