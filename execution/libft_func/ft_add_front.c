/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:51:31 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:59:27 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_add_front(t_built *head, char *var, char *value)
{
	t_built	*new_node;

	new_node = malloc(sizeof(t_built));
	if (!new_node)
		return (head);
	new_node->var = ft_strdup(var);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = head;
	return (new_node);
}
