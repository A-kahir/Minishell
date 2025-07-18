/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:12 by akahir            #+#    #+#             */
/*   Updated: 2025/07/18 20:48:45 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_rm_list(t_built **head, t_built *target)
{
	t_built	*temp;
	t_built	*prv = NULL;

	if (!target || !head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp == target)
		{
			if (prv == NULL)
				*head = temp->next;
			else
				prv->next = temp->next;

			if (temp && temp->var)
				free(temp->var);
			temp->var = NULL;
			if (temp && temp->value)
				free(temp->value);
			temp->value = NULL;
			// if (temp && temp->old_pwd)
			// 	free(temp->old_pwd);
			temp->old_pwd = NULL;
			temp->pwd = NULL;
			if (temp)
				free(temp);
			temp = NULL;
			return;
		}
		prv = temp;
		temp = temp->next;
	}
}
