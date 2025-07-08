/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:03 by akahir            #+#    #+#             */
/*   Updated: 2025/07/08 17:41:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_only_print(t_built *line)
{
	t_built	*curr;

	curr = line;
	curr = ft_sort_vars(curr);
	while (curr)
	{
		if ((ft_strcmp(curr->var, "PATH") == 0
				&& ft_strcmp(curr->next->var, "PWD") == 0
				&& ft_strcmp(curr->next->next->var, "SHLVL") == 0)
			|| (ft_strcmp(curr->var, "_") == 0
				&& curr->value && ft_strcmp(curr->value, "/usr/bin/env") == 0))
		{
			curr = curr->next;
			continue ;
		}
		if (ft_strcmp(curr->value, "/mnt/homes/akahir/Desktop/Minishell/./minishell") == 0)
			curr = curr->next;
		if (curr->var)
		{
			write(1, "declare -x ", 11);
			printf("%s", curr->var);
			if (curr->value)
				printf("=\"%s\"", curr->value);
			printf("\n");
		}
		curr = curr->next;
	}
}
