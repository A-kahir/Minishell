

#include "execution.h"

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

static	char	*join_path(char *dir, char *cmd)
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

char **ft_get_path(char *cmd, char **env)
{
	char **cmd_args;
	char **paths;
	char *full_path;
	int i;

	if (is_only_spaces(cmd))
		return (NULL);

	// ⛔️ Avoid splitting cmd again if it's already a word like "ls"
	cmd_args = malloc(sizeof(char *) * 2);
	if (!cmd_args)
		return (NULL);
	cmd_args[0] = ft_strdup(cmd);
	cmd_args[1] = NULL;
	if (!cmd_args[0])
		return (free(cmd_args), NULL);

	// If command contains a path, try it directly
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
			return (cmd_args);
		else
			return (free_split(cmd_args), NULL);
	}

	// Search in PATH
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (free_split(cmd_args), NULL);

	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (free_split(cmd_args), NULL);

	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd_args[0]);
		if (!full_path)
			continue;
		if (access(full_path, X_OK) == 0)
		{
			free(cmd_args[0]);
			cmd_args[0] = full_path;
			free_split(paths);
			return (cmd_args);
		}
		free(full_path);
	}
	return (free_split(paths), free_split(cmd_args), NULL);
}

