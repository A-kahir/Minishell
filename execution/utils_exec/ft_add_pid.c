/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:02:25 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 19:48:33 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_pid_list	*ft_add_pid(t_pid_list *head, pid_t pid)
{
	t_pid_list	*new;
	t_pid_list	*temp;

	new = malloc_cl(sizeof(t_pid_list), 0, 0);
	if (!new)
		return (head);
	new->pid = pid;
	new->next = NULL;
	if (!head)
		return (new);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (head);
}
