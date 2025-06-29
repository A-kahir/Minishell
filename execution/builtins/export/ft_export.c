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

int ft_check_alr_have(char *var, t_built *curr)
{
	t_built *tmp;

	tmp = curr;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static	void	ft_we_have_var(t_built *line_env, char **cmd)
{
	int	i;
	int	j;
	int	check;
	int	flag;
	t_built *curr;

	i = 1;
	while (cmd[i])
	{
		check = ft_specify_var(cmd[i]);
		if (check == 1)
		{
			ft_is_positif(line_env, cmd[i]);
			i++;
			continue ;
		}
		if (cmd[i][0] == '$')
		{
			curr = line_env;
			j = 0;
			while (cmd[j])
			{
				if (ft_check_alr_have(cmd[j], curr) == 0)
				{
					flag = 1;
				}
				else 
					flag = 0;
				curr = curr->next;
				j++;
			}
			if (flag == 0)
			{
				ft_only_print(line_env);
				return ;
			}
		}
		else if (check == -1)
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			return ;
		}
		else if (check == 0)
			ft_add_var(line_env, cmd[i]);
		i++;
	}
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
