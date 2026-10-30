/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:22:57 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 14:32:44 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	free_leaks_list(t_leaks **head)
{
	t_leaks	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->ptr);
		free(tmp);
	}
}

static void	*ft_cantinue(size_t size, t_leaks **head)
{
	void		*ptr;
	t_leaks		*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_leaks));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
	return (ptr);
}

void	*malloc_cl(size_t size, t_mode mode, int is_static)
{
	static t_leaks	*temp_head = NULL;
	static t_leaks	*static_head = NULL;

	if (mode == FREE_TEMP || mode == FREE_ALL)
	{
		free_leaks_list(&temp_head);
		if (mode != FREE_ALL)
			return (NULL);
	}
	if (mode == FREE_STRUCT || mode == FREE_ALL)
	{
		free_leaks_list(&static_head);
		return (NULL);
	}
	if (is_static)
		return (ft_cantinue(size, &static_head));
	return (ft_cantinue(size, &temp_head));
}
