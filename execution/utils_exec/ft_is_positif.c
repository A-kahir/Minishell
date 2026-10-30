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
		temp = ft_strjoin(curr->value, append_str, 1);
	else
		temp = ft_strdup(append_str, 0, 1);
	curr->value = temp;
}

static void	ft_add_to_export(t_built *curr, char **var,
	char *skip_eq, t_built *line_env)
{
	while (curr)
	{
		if (ft_strcmp(curr->var, var[0]) == 0)
		{
			ft_take_val(curr, skip_eq);
			break ;
		}
		else if (curr->next == NULL)
		{
			ft_add_back(line_env, var[0], skip_eq);
			break ;
		}
		curr = curr->next;
	}
}

void	ft_is_positif(t_built *line_env, char *cmd)
{
	t_built	*curr;
	char	**var;
	char	*skip_eq;
	char	*equal_pos;

	equal_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	if (!equal_pos)
		return ;
	var = malloc_cl(sizeof(char *) * 3, 0, 0);
	if (!var)
		return ;
	var[0] = ft_substr(cmd, 0, equal_pos - cmd);
	var[1] = ft_strdup(equal_pos + 2, 0, 0);
	var[2] = NULL;
	if (!var[0] || !var[1])
		return ;
	skip_eq = var[1];
	curr = line_env;
	ft_add_to_export(curr, var, skip_eq, line_env);
	ft_free_split(var);
}
