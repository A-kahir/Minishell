/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:24:39 by akahir            #+#    #+#             */
/*   Updated: 2025/07/24 20:28:54 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static t_built	*ft_cd_normal_fail(t_built *line_env, t_exec *in)
{
	char	*home;

	perror("minishell: cd");
	home = getcwd(NULL, 0);
	if (home)
	{
		line_env->old_pwd = ft_strdup(home, 0, 1);
		free(home);
	}
	in->status = NULL;
	in->status = ft_strdup("1", 0, 0);
	return (line_env);
}

static t_built	*ft_cd_normal_succ(char **str, t_built *line_env, int *flag_cd)
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
			line_env->pwd = ft_strdup(str[1], 0, 1);
	}
	*flag_cd = 1;
	return (line_env);
}

t_built	*ft_cd_normal(char **str, t_built *line_env,
int *flag_cd, t_exec *in)
{
	if (chdir(str[1]) == -1)
	{
		return (ft_cd_normal_fail(line_env, in));
	}
	else
	{
		return (ft_cd_normal_succ(str, line_env, flag_cd));
	}
}
