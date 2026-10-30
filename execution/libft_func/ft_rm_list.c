/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:12 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 14:27:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_rm_list(t_built **head, t_built *target)
{
	t_built	*temp;
	t_built	*prv;

	if (!target || !head || !*head)
		return ;
	prv = NULL;
	temp = *head;
	while (temp)
	{
		if (temp == target)
		{
			if (prv == NULL)
				*head = temp->next;
			else
				prv->next = temp->next;
			temp->var = NULL;
			temp->value = NULL;
			temp->old_pwd = NULL;
			temp->pwd = NULL;
			temp = NULL;
			return ;
		}
		prv = temp;
		temp = temp->next;
	}
}
