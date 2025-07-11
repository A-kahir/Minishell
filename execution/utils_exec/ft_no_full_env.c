/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_full_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:58:00 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 17:58:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_already_exists(t_built *line_env, char *var)
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

void	ft_no_full_env(t_built *line_env)
{
	char *pwd;

	if (!ft_already_exists(line_env, "PATH"))
		ft_add_back(line_env, "PATH", PATH_ENV);
	if (!ft_already_exists(line_env, "PWD"))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			ft_add_back(line_env, "PWD", pwd);
			free(pwd);
		}
	}
	if (!ft_already_exists(line_env, "SHLVL"))
		ft_add_back(line_env, "SHLVL", "1");
	if (!ft_already_exists(line_env, "OLDPWD"))
		ft_add_back(line_env, "OLDPWD", NULL);
}

