/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_full_env_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:24:55 by akahir            #+#    #+#             */
/*   Updated: 2025/07/16 12:31:06 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_already_exists_f(t_built *line_env, char *var)
{
	t_built	*curr;

	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, var) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_built *ft_no_full_env_f(t_built *line_env)
{
	char *pwd;

	if (!ft_already_exists_f(line_env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			line_env = ft_add_back(line_env, "PWD", pwd);
			free(pwd);
		}
	}
	if (!ft_already_exists_f(line_env, "SHLVL"))
		line_env = ft_add_back(line_env, "SHLVL", "1");

	if (!ft_already_exists_f(line_env, "OLDPWD"))
		line_env = ft_add_back(line_env, "OLDPWD", NULL);
	return (line_env);
}