/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:09:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void	cantinue(t_built *line_env, char **cmd, int flag)
{
	int	i;
	int	check;
	int	print;

	i = 1;
	print = 0;
	if (flag == 0)
	{
		while (cmd[i++])
		{
			if (cmd[i] &&cmd[i][0] == '$' && print++ == 0)
				ft_only_print(line_env);
		}
	}
	else
	{
		while (cmd[i++])
		{
			check = ft_specify_var(cmd[i]);
			if (check == 1)
				ft_is_positif(line_env, cmd[i]);
			else if (check == 0)
				ft_add_var(line_env, cmd[i]);
		}
	}
}

static void	ft_we_have_var(t_built *line_env, char **cmd)
{
	int	i;
	int	check;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		check = ft_specify_var(cmd[i]);
		if (ft_strchr(cmd[i], '='))
			flag = 1;
		else if (ft_strchr(cmd[i], '$') || check == 4)
			flag = 0;
		if (check == -1)
		{
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
			return ;
		}
		i++;
	}
	cantinue(line_env, cmd, flag);
}

t_built	*ft_export(t_built *line_env, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
	{
		ft_only_print(line_env);
	}
	else if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL)
	{
		ft_we_have_var(line_env, cmd);
	}
	return (line_env);
}
