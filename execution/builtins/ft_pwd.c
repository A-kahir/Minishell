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

char	*handle_pwd_error(t_built *line_env)
{
	t_built	*curr;
	int		flag_have_env;

	flag_have_env = ft_check_no_env(line_env);
	curr = line_env;
	while (curr)
	{
		if (flag_have_env == 0)
		{
			write(1, curr->pwd, ft_strlen(curr->pwd));
			write(1, "\n", 2);
			break ;
		}
		if (flag_have_env == 1
			&& ft_strcmp(curr->var, "PWD") != 0 && curr->next == NULL)
		{
			write(2, "pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 110);
			return (ft_strdup("1", 0, 0));
		}
		curr = curr->next;
	}
	return ("0");
}

char	*ft_pwd_back(t_built *line_env)
{
	t_built	*curr;
	int		flag;

	flag = 1;
	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, "PWD") == 0)
		{
			return ((write(1, curr->value, ft_strlen(curr->value)),
					write(1, "\n", 2), "0"));
		}
		else if (ft_strcmp(curr->var, "PWD") != 0 && curr->next == NULL)
			flag = 1;
		curr = curr->next;
	}
	if (line_env && line_env->pwd && flag == 0)
		printf("%s\n", line_env->pwd);
	else if (line_env && line_env->old_pwd && flag == 0)
		printf("%s\n", line_env->old_pwd);
	else if (flag == 1)
		return (handle_pwd_error(line_env));
	return ("0");
}

char	*ft_pwd(t_built *line_env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		return ((printf("%s\n", path)), (free(path)), "0");
	else
		return (ft_pwd_back(line_env));
}
