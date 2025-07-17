/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_pro_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:15:06 by akahir            #+#    #+#             */
/*   Updated: 2025/07/16 12:16:21 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execution.h"

char	**ft_get_path_f(char *cmd, char **env, t_built *line_env)
{
	char			**cmd_args;
	struct stat		data;

	if (!cmd)
		return (NULL);
	if (is_only_spaces(cmd))
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (cmd_args &&  cmd_args[1])
		return (NULL);
	if (!cmd_args || !cmd_args[0])
		return (NULL);
	if (ft_strchr(cmd_args[0], '/'))
	{
		errno = 0;
		if (access(cmd_args[0], X_OK) == 0)
		{
			if (stat(cmd_args[0], &data) == 0 && S_ISDIR(data.st_mode))
			{
				write(2, "minishell: ", 12);
				write(2, cmd_args[0], ft_strlen(cmd_args[0]));
				write(2, ": is a directory\n", 18);
				exit(126);
			}
			return (cmd_args);
		}
		else
		{
			if (errno == ENOTDIR)
			{
				write(2, "minishell: ", 12);
				write(2, cmd_args[0], ft_strlen(cmd_args[0]));
				write(2, ": Not a directory\n", 19);
				exit(126);
			}
			else if (errno == ENOENT)
			{
				write(2, "minishell: ", 12);
				write(2, cmd_args[0], ft_strlen(cmd_args[0]));
				write(2, ": No such file or directory\n", 29);
				exit(127);
			}
			else
			{
				write(2, "minishell: ", 12);
				write(2, cmd_args[0], ft_strlen(cmd_args[0]));
				write(2, ": Permission denied\n", 21);
				exit(126);
			}
			return (NULL);
		}
	}
    return (NULL);
}


void ft_child_pro_f(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
	char	**cmd_args;
	int flag_redir;
	char *command;

	command = ft_check_built_redir(curr);
	flag_redir = ft_flag_redir(curr);
	if (in.i > 0 && dup2(in.pipes[in.i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (in.i < in.n_cmds - 1 && dup2(in.pipes[in.i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(in.pipes, in.n_cmds);
	if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
	{
		int status = ft_is_builtins(curr, line_env, &in);
		exit(status);
	}
	if (flag_redir == 1)
	{
		int status = ft_is_redir(curr, line_env, env_here, in);
		exit(status);
	}
	if (curr->cmd[0] == NULL && ft_check_this_var(curr->cmd[0] + 1, line_env) == 1)
		exit(0);
	cmd_args = ft_get_path_f(curr->cmd[0], env_here.env, line_env);
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 12);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	else if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
		(perror("execve failed"), ft_free_split(cmd_args), exit(1));
} 
