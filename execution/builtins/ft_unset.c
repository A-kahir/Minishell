/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:32:17 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:37:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_unset_var(t_built *line_env, char *var)
{
	t_built	*curr;

	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, var) == 0)
		{
			curr->var = NULL;
			curr->var = ft_strdup("\0", 0, 1);
			curr->value = NULL;
			curr->value = ft_strdup("\0", 0, 1);
			break ;
		}
		curr = curr->next;
	}
}

t_built	*ft_unset(t_built *line_env, char **cmd, t_exec *in)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '/'))
		{
			write(2, "minishell: unset: `", 20);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 27);
			in->status = ft_strdup("1", 0, 0);
			flag = 1;
		}
		else
			ft_unset_var(line_env, cmd[i]);
		i++;
	}
	if (flag == 0)
		in->status = ft_strdup("0", 0, 0);
	return (line_env);
}
