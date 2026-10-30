/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:10:45 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 16:10:45 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(dir, "/", 0);
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd, 0);
	return (full_path);
}

static char	**ft_get_paths_from_env(char **env, char **cmd_args)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
	{
		ft_free_split(cmd_args);
		return (NULL);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
	{
		ft_free_split(cmd_args);
		return (NULL);
	}
	return (paths);
}

static char	**search_in_path(char **cmd_args, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_get_paths_from_env(env, cmd_args);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd_args[0]);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (access(full_path, X_OK) == 0)
			return (cmd_args[0] = full_path, ft_free_split(paths), cmd_args);
		i++;
	}
	return (ft_free_split(paths), ft_free_split(cmd_args), NULL);
}

char	**ft_get_path(char *cmd, char **env)
{
	char	**cmd_args;

	if (is_only_spaces(cmd))
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0] || cmd_args[1])
		return (NULL);
	if (ft_strchr(cmd_args[0], '/'))
		return (ft_have_slash(cmd_args));
	return (search_in_path(cmd_args, env));
}
