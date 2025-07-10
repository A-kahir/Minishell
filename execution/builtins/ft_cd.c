/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/07/10 19:25:35 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_cd(char **str, t_built *line_env, int *flag_cd)
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
		*flag_cd = 1;
	}
	else if (ft_strcmp(str[0], "cd") == 0)
	{
		if (chdir(str[1]) == -1)
		{
			write(2, "minishell: cd: ", 16);
			write(2, str[1], ft_strlen(str[1]));
			write(2, ": No such file or directory\n", 29);
		}
		else
		{
			home = getcwd(NULL, 0);
			line_env->pwd = ft_strdup(home);
			free(home);
			*flag_cd = 1;
		}
	}
	return (line_env);
}
