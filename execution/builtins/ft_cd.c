/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/07/27 15:32:23 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static t_built	*ft_cd_home(t_built *line_env,
int *flag_cd, t_exec *in)
{
	t_built	*curr;
	char	*home;

	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, "HOME") == 0)
		{
			home = curr->value;
			if (!home || chdir(home) != 0)
				return (perror("cd"), in->status = NULL,
					(in->status = ft_strdup("1", 0, 0)), line_env);
			break ;
		}
		else if (curr->next == NULL && ft_strcmp(curr->var, "HOME") != 0)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			in->status = NULL;
			in->status = ft_strdup("1", 0, 0);
			return (line_env);
		}
		curr = curr->next;
	}
	*flag_cd = 1;
	return (line_env);
}

t_built	*ft_cd_parent_helper(t_built *line_env, char *curr_pwd,
int *flag_cd, t_exec *in)
{
	char	*parent_pth;
	char	*home;

	parent_pth = ft_parent_dir(curr_pwd);
	if (parent_pth)
	{
		if (chdir(parent_pth) == 0)
		{
			home = getcwd(NULL, 0);
			if (home)
			{
				line_env->pwd = ft_strdup(home, 0, 1);
			}
			else
			{
				write(2, "cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 109);
				line_env->pwd = ft_strdup(parent_pth, 0, 1);
			}
			*flag_cd = 1;
			in->status = ft_strdup("0", 0, 0);
			return (line_env);
		}
	}
	return (NULL);
}

t_built	*ft_cd(char **str, t_built *line_env, int *flag_cd, t_exec *in)
{
	if (!str)
		return (line_env);
	if (ft_strcmp(str[0], "cd") == 0 && !str[1])
		return (ft_cd_home(line_env, flag_cd, in));
	else if (ft_strcmp(str[0], "cd") == 0)
	{
		if (ft_strcmp(str[1], "..") == 0)
			return ((in->status = ft_strdup("0", 0, 0)),
				ft_cd_parent(str, line_env, flag_cd, in));
		else
			return ((in->status = ft_strdup("0", 0, 0)),
				ft_cd_normal(str, line_env, flag_cd, in));
	}
	in->status = ft_strdup("0", 0, 0);
	return (line_env);
}
