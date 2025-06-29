/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:41 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 15:28:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_take_val(t_built *curr, char *append_str)
{
	char	*temp;

	if (curr->value)
		temp = ft_strjoin(curr->value, append_str);
	else
		temp = ft_strdup(append_str);
	free(curr->value);
	curr->value = temp;
}

static void	ft_add_to_export(t_built *curr, char **var,
	char *skip_equal, t_built *line_env)
{
	while (curr)
	{
		if (ft_strcmp(curr->var, var[0]) == 0)
		{
			ft_take_val(curr, skip_equal);
			break ;
		}
		else if (curr->next == NULL)
		{
			ft_add_back(line_env, var[0], skip_equal);
			break ;
		}
		curr = curr->next;
	}
}

void	ft_is_positif(t_built *line_env, char *cmd)
{
	t_built	*curr;
	char	**var;
	char	*skip_equal;

	var = ft_split(cmd, '+');
	if (!var || !var[0] || !var[1])
	{
		ft_free_split(var);
		return ;
	}
	skip_equal = ft_strdup(var[1] + 1);
	curr = line_env;
	ft_add_to_export(curr, var, skip_equal, line_env);
	free(skip_equal);
	ft_free_split(var);
}
