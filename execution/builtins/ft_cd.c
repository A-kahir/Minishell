/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/07/15 18:02:16 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built	*ft_cd(char **str, t_built *line_env, int *flag_cd, t_exec *in)
{
	t_built	*curr;
	char	*home;

	curr = line_env;
	if (str && str[0] && str[1] && str[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		in->status = NULL;
		in->status = ft_strdup("1");
		return (line_env);
	}
	if (ft_strcmp(str[0], "cd") == 0 && !str[1])
	{
		while (curr)
		{
			if (ft_strcmp(curr->var, "HOME") == 0)
			{
				home = curr->value;
				if (!home || chdir(home) != 0)
				{
					perror("cd");
					in->status = NULL;
					in->status = ft_strdup("1");
					return (line_env);
				}
				break ;
			}
			else if (curr->next == NULL && ft_strcmp(curr->var, "HOME") != 0)
			{
				write(2, "minishell: cd: HOME not set\n", 29);
				in->status = NULL;
				in->status = ft_strdup("1");
				return (line_env);
			}
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
			in->status = NULL;
			in->status = ft_strdup("1");
			return (line_env);

		}
		else
		{
			home = getcwd(NULL, 0);
			line_env->pwd = ft_strdup(home);
			free(home);
			*flag_cd = 1;
		}
	}
	in->status = ft_strdup("0");
	return (line_env);
}
