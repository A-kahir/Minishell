/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:52:56 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 18:53:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_check_path_var(t_data *data,
t_built *line_env, int *flag_one_pth)
{
	t_built	*curr;

	if (ft_strcmp(data->cmd[0], "export") == 0
		&& ft_strcmp(data->cmd[1], "PATH") == 0)
	{
		curr = line_env;
		while (curr)
		{
			if (ft_strcmp(curr->var, "PATH") == 0
				&& ft_strcmp(curr->value,
					"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == 0)
			{
				*flag_one_pth = 1;
				break ;
			}
			curr = curr->next;
		}
	}
}
