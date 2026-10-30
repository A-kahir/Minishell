/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:22:21 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 18:56:48 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static t_built	*ft_cd_parent_fail(t_built *line_env, int *flag_cd, t_exec *in)
{
	if (access(".", R_OK) == -1 && chdir("/") == 0)
	{
		line_env->pwd = ft_strdup("/", 0, 1);
		*flag_cd = 1;
		in->status = ft_strdup("0", 0, 0);
		return (line_env);
	}
	perror("minishell: cd");
	in->status = NULL;
	in->status = ft_strdup("1", 0, 0);
	return (line_env);
}

static t_built	*ft_cd_parent_succ(t_built *line_env, int *flag_cd)
{
	char	*home;

	home = getcwd(NULL, 0);
	if (home)
	{
		line_env->pwd = ft_strdup(home, 0, 1);
		free(home);
	}
	else
	{
		write(2, "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 109);
		if (access(".", R_OK) == -1 && chdir("/") == 0)
			line_env->pwd = ft_strdup("/", 0, 1);
		else
			line_env->pwd = ft_strdup("..", 0, 1);
	}
	*flag_cd = 1;
	return (line_env);
}

t_built	*ft_cd_parent(char **str, t_built *line_env, int *flag_cd, t_exec *in)
{
	char	*curr_pwd;
	t_built	*result;

	if (chdir(str[1]) == -1)
	{
		curr_pwd = getcwd(NULL, 0);
		if (!curr_pwd)
		{
			curr_pwd = ft_strdup(line_env->pwd, 0, 1);
			if (!curr_pwd)
				curr_pwd = ft_strdup("/", 0, 1);
		}
		if (curr_pwd)
		{
			result = ft_cd_parent_helper(line_env, curr_pwd, flag_cd, in);
			if (result)
				return (result);
		}
		return (ft_cd_parent_fail(line_env, flag_cd, in));
	}
	else
		return (ft_cd_parent_succ(line_env, flag_cd));
}
