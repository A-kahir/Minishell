/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:25 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:11:07 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_chack_pth(t_built * curr)
{
	while (curr)
	{
		if (ft_strcmp(curr->value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == 0)
		{
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static void	ft_print_env_vars(t_built *curr)
{
	int skip;

	skip = ft_chack_pth(curr);
	while (curr)
	{
		if (skip == 1)
		{
			if (curr && ft_strcmp(curr->value, "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == 0)
			{
				curr = curr->next;
				continue ;
			}
			if (curr && ft_strcmp(curr->value, "/usr/bin/env") == 0)
			{
				curr = curr->next;
				continue ;
			}
		}
		if (curr && ft_strcmp(curr->value, "/mnt/homes/akahir/Desktop/Minishell/./minishell") == 0)
			curr = curr->next;
		if (curr && curr->var && curr->value)
			printf("%s=%s\n", curr->var, curr->value);
		curr = curr->next;
	}
}

t_built	*ft_env(t_built *line_env)
{
	t_built		*curr;
	t_built		*tmp;

	if (line_env)
	{
		tmp = line_env;
		while (tmp)
		{
			if (ft_strcmp(tmp->value, "/usr/bin/env") != 0 && tmp->next == NULL)
				line_env = ft_add_back(line_env, "_", "/usr/bin/env");
			tmp = tmp->next;
		}
		curr = line_env;
		ft_print_env_vars(curr);
	}
	return (line_env);
}
