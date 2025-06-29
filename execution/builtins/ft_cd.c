/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:47:13 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_cd(char **str, t_built *line_env)
{
	t_built	*curr;
	char	*home;

	curr = line_env;
	if (ft_strcmp(str[0], "cd") == 0 && !str[1])
	{
		while (curr)
		{
			if (ft_strcmp(curr->var, "HOME") == 0)
			{
				home = getenv("HOME");
				if (!home || chdir(home) != 0)
					perror("cd");
			}
			else if (curr->next == NULL && ft_strcmp(curr->var, "HOME") == 0)
				write(2, "minishell: cd: HOME not set\n", 29);
			curr = curr->next;
		}
	}
	else if (ft_strcmp(str[0], "cd") == 0 && chdir(str[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", str[1]);
	}
	return (line_env);
}
