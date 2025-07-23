/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/07/23 11:13:30 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_parent_dir(char *current_path)
{
	char	*parent_pth;
	char	*last_slash;
	int		len;
	if (!current_path || ft_strcmp(current_path, "/") == 0)
		return (ft_strdup("/"));
	len = ft_strlen(current_path);
	parent_pth = ft_strdup(current_path);
	if (len > 1 && parent_pth[len - 1] == '/')
		parent_pth[len - 1] = '\0';
	last_slash = ft_strrchr(parent_pth, '/');
	if (last_slash)
	{
		if (last_slash == parent_pth)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
	}
	else
	{
		free(parent_pth);
		return (ft_strdup("/"));
	}
	return (parent_pth);
}

t_built	*ft_cd(char **str, t_built *line_env, int *flag_cd, t_exec *in)
{
	t_built	*curr;
	char	*home;
	char	*curr_pwd;
	char	*parent_pth;
	curr = line_env;
	
	if (str && str[0] && str[1] && str[2] && !ft_strchr(str[1], '/'))
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
		if (ft_strcmp(str[1], "..") == 0)
		{
			if (chdir(str[1]) == -1)
			{
				curr_pwd = getcwd(NULL, 0);
				if (!curr_pwd)
				{
					curr_pwd = ft_strdup(line_env->pwd);
					if (!curr_pwd)
						curr_pwd = ft_strdup("/");
				}
				if (curr_pwd)
				{
					parent_pth = ft_parent_dir(curr_pwd);
					if (parent_pth)
					{
						if (chdir(parent_pth) == 0)
						{
							free(curr_pwd);
							home = getcwd(NULL, 0);
							if (home)
							{
								line_env->pwd = ft_strdup(home);
								free(home);
							}
							else
							{
								write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 109);
								line_env->pwd = ft_strdup(parent_pth);
							}
							free(parent_pth);
							*flag_cd = 1;
							in->status = ft_strdup("0");
							return (line_env);
						}
						free(parent_pth);
					}
					free(curr_pwd);
				}
				if (access(".", R_OK) == -1 && chdir("/") == 0)
				{
					line_env->pwd = ft_strdup("/");
					*flag_cd = 1;
					in->status = ft_strdup("0");
					return (line_env);
				}
				perror("minishell: cd");
				in->status = NULL;
				in->status = ft_strdup("1");
				return (line_env);
			}
			else
			{
				home = getcwd(NULL, 0);
				if (home)
				{
					line_env->pwd = ft_strdup(home);
					free(home);
				}
				else
				{
					write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 109);
					if (access(".", R_OK) == -1 && chdir("/") == 0)
						line_env->pwd = ft_strdup("/");
					else
						line_env->pwd = ft_strdup("..");
				}
				*flag_cd = 1;
			}
		}
		else
		{
			if (chdir(str[1]) == -1)
			{
				perror("minishell: cd");
				home = getcwd(NULL, 0);
				if (home)
				{
					line_env->old_pwd = ft_strdup(home);
					free(home);
				}
				in->status = NULL;
				in->status = ft_strdup("1");
				return (line_env);
			}
			else
			{
				home = getcwd(NULL, 0);
				if (home)
				{
					line_env->pwd = ft_strdup(home);
					free(home);
				}
				else
				{
					write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 109);
					if (access(".", R_OK) == -1 && chdir("/") == 0)
						line_env->pwd = ft_strdup("/");
					else
						line_env->pwd = ft_strdup(str[1]);
				}
				*flag_cd = 1;
			}
		}
	}
	in->status = ft_strdup("0");
	return (line_env);
}
