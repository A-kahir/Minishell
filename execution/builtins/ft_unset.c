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

t_built	*ft_unset(t_built *line_env, char **cmd, t_exec *in)
{
	t_built	*curr;
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (cmd[i])
	{
		curr = line_env;
		if (ft_strchr(cmd[i], '/'))
		{
			write(2, "minishell: unset: `", 20);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 27);
			in->status = NULL;
			in->status = ft_strdup("1");
			flag = 1;
			return (line_env);
		}
		while (curr)
		{
			if (ft_strcmp(curr->var, cmd[i]) == 0)
			{
				ft_rm_list(&line_env, curr);
				break ;
			}
			curr = curr->next;
		}
		i++;
	}
	if (flag == 0)
		in->status = ft_strdup("0");
	return (line_env);
}
