/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:56:46 by akahir            #+#    #+#             */
/*   Updated: 2025/05/29 16:15:07 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_flag_redir(t_data *data)
{
	t_data *curr = data;

	while (curr)
	{
		if (curr->redir && curr->redir->type != -1)
			return (1);
		curr = curr->next;
	}
	return (0);
}


