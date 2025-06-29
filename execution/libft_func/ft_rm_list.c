/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:12 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:59:48 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_rm_list(t_built **head, t_built *target)
{
	t_built	*temp;
	t_built	*prv;

	temp = *head;
	prv = NULL;
	while (temp)
	{
		if (temp == target)
		{
			if (prv == NULL)
				*head = temp->next;
			else
				prv->next = temp->next;
			free(temp->var);
			free(temp->value);
			free(temp);
			return ;
		}
		prv = temp;
		temp = temp->next;
	}
}
