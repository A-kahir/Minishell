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

static int	is_only_spaces(char *cmd)
{
	int	i;

	if (!cmd || *cmd == 0)
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
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
		{
			free(cmd_args[0]);
			return (cmd_args[0] = full_path, ft_free_split(paths), cmd_args);
		}
		free(full_path);
		i++;
	}
	return (ft_free_split(paths), ft_free_split(cmd_args), NULL);
}

char	**ft_get_path(char *cmd, char **env, t_built *line_env)
{
	char	**cmd_args;
	struct stat data;

	if (is_only_spaces(cmd))
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		return (NULL);
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
		{
			if (stat(cmd, &data) == 0 && S_ISDIR(data.st_mode))
			{
				write(2, "minishell: ", 12);
				write(2, cmd, ft_strlen(cmd));
				write(2, ": is a directory\n", 18);
				exit(126);
			}
		}
		else if (errno == 20)
		{
			write(2, "minishell: ", 12);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Not a directory\n", 19);
			exit(126);
		}
		else
		{
			ft_free_split(cmd_args);
			return (NULL);
		}
	}
	return (search_in_path(cmd_args, env));
}
