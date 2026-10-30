/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_hered.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:25:07 by akahir            #+#    #+#             */
/*   Updated: 2025/07/27 18:01:39 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_check_hered(t_redir *redir)
{
	t_redir	*curr;
	int		i;

	curr = redir;
	i = 0;
	while (curr)
	{
		if (curr->type == 3)
			i++;
		if (i >= 16)
		{
			write(2, "bash: maximum here-document count exceeded\n", 44);
			malloc_cl(0, 3, 0);
			exit(2);
		}
		curr = curr->next;
	}
}
