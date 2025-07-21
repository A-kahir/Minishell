/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/07/21 13:42:41 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_parent_directory(char *current_path)
{
	char	*parent_path;
	char	*last_slash;
	int		len;
	if (!current_path || ft_strcmp(current_path, "/") == 0)
		return (ft_strdup("/"));
	len = ft_strlen(current_path);
	parent_path = ft_strdup(current_path);
	if (len > 1 && parent_path[len - 1] == '/')
		parent_path[len - 1] = '\0';
	last_slash = ft_strrchr(parent_path, '/');
	if (last_slash)
	{
		if (last_slash == parent_path)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
	}
	else
	{
		free(parent_path);
		return (ft_strdup("/"));
	}
	return (parent_path);
}

t_built	*ft_cd(char **str, t_built *line_env, int *flag_cd, t_exec *in)
{
	t_built	*curr;
	char	*home;
	char	*current_pwd;
	char	*parent_path;
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
		if (ft_strcmp(str[1], "..") == 0)
		{
			if (chdir(str[1]) == -1)
			{
				current_pwd = getcwd(NULL, 0);
				if (!current_pwd)
				{
					current_pwd = ft_strdup(line_env->pwd);
					if (!current_pwd)
						current_pwd = ft_strdup("/");
				}
				if (current_pwd)
				{
					parent_path = get_parent_directory(current_pwd);
					if (parent_path)
					{
						if (chdir(parent_path) == 0)
						{
							free(current_pwd);
							home = getcwd(NULL, 0);
							if (home)
							{
								line_env->pwd = ft_strdup(home);
								free(home);
							}
							else
							{
								write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 109);
								line_env->pwd = ft_strdup(parent_path);
							}
							free(parent_path);
							*flag_cd = 1;
							in->status = ft_strdup("0");
							return (line_env);
						}
						free(parent_path);
					}
					free(current_pwd);
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
