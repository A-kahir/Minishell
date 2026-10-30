/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:02:51 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 14:26:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_rm_list_env(t_built **head, t_built *rm_node)
{
	t_built	*curr;
	t_built	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr == rm_node)
		{
			if (prev == NULL)
				*head = curr->next;
			else
				prev->next = curr->next;
			if (curr->var)
				curr->var = NULL;
			if (curr->value)
				curr->value = NULL;
			curr = NULL;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
