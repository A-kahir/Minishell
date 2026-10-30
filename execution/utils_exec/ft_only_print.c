/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:31:03 by akahir            #+#    #+#             */
/*   Updated: 2025/07/29 20:13:20 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_print_declare_line(t_built *curr)
{
	if (curr->var[0] != '\0')
	{
		if (curr->var)
		{
			write(1, "declare -x ", 11);
			printf("%s", curr->var);
			if (curr->value)
				printf("=\"%s\"", curr->value);
			printf("\n");
		}
	}
}

static void	ft_print_export(t_built *curr, int flag_one_pth)
{
	while (curr)
	{
		if (curr
			&& ft_strcmp(curr->var, "PATH") == 0
			&& curr->next
			&& curr->next->var
			&& ft_strcmp(curr->next->var, "PWD") == 0
			&& curr->next->next
			&& curr->next->next->var
			&& ft_strcmp(curr->next->next->var, "SHLVL") == 0
			&& flag_one_pth == 0)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->value && ft_strcmp(curr->value, "/usr/bin/env") == 0)
		{
			curr = curr->next;
			continue ;
		}
		ft_print_declare_line(curr);
		curr = curr->next;
	}
}

void	ft_only_print(t_built *line, int flag_one_pth)
{
	t_built	*curr;

	if (!*(line->var) && line->var[0] != '\0')
		return ;
	curr = line;
	while (curr)
	{
		if (ft_strcmp(curr->var, "PATH")
			&& ft_strcmp(curr->value,
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == 0
			&& flag_one_pth == 1)
		{
			ft_add_back(line, curr->var, curr->value);
			break ;
		}
		curr = curr->next;
	}
	curr = line;
	curr = ft_sort_vars(curr);
	ft_print_export(curr, flag_one_pth);
}
