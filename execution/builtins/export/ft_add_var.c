/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:04 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 12:31:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static int	ft_update_existing_var(t_built *line_env, char *var, char *value)
{
	t_built	*curr;

	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, var) == 0)
		{
			if (value)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_add_var(t_built *line_env, char *cmd)
{
	char	*equal;
	char	*var;
	char	*value;
	int		found;

	equal = ft_strchr(cmd, '=');
	var = NULL;
	value = NULL;
	if (equal)
	{
		var = ft_substr(cmd, 0, equal - cmd);
		value = ft_strdup(equal + 1);
	}
	else
		var = ft_strdup(cmd);
	if (!var || var[0] == '\0')
	{
		free(var);
		if (value)
			free(value);
		return;
	}
	found = ft_update_existing_var(line_env, var, value);
	if (!found)
		ft_add_back(line_env, var, value);
	free(var);
	if (value)
		free(value);
}
