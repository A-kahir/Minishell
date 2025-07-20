/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:31:45 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:22:44 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_pwd(t_built *line_env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		return (ft_strdup("0"));
	}
	else
	{
		t_built *curr = line_env;
		while (curr)
		{
			if (ft_strcmp(curr->var, "PWD") == 0)
			{
				printf("%s\n", curr->value);
				return ft_strdup("0");
			}
			curr = curr->next;
		}
		if (line_env->pwd)
		{
			printf("%s\n", line_env->pwd);
		}
		else if (line_env && line_env->old_pwd)
		{

			printf("%s\n", line_env->old_pwd);
		}
		else
		{
			t_built *curr;

			curr = line_env;
			while (curr)
			{
				if (ft_strcmp(curr->var, "PWD") != 0 && curr->next == NULL)
				{
					write(2, "pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 110);
					return (ft_strdup("1"));
				}
				curr = curr->next;
			}
		}
		return (ft_strdup("0"));
	}
}
