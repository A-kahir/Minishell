/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:09:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 19:56:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_child_pro(t_data *curr, char **env, t_exec in)
{
	char	**cmd_args;

	if (in.i > 0 && dup2(in.pipes[in.i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (in.i < in.n_cmds - 1 && dup2(in.pipes[in.i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(in.pipes, in.n_cmds);
	cmd_args = ft_get_path(curr->cmd[0], env);
	if (!cmd_args)
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
	if (execve(cmd_args[0], curr->cmd, env) == -1)
	{
		(perror("execve failed"), ft_free_split(cmd_args), exit(1));
	}
}

void	ft_child_prop(t_data *curr, t_built *line_env, char **env, t_exec in)
{
	char	**cmd_args;

	if (in.i > 0 && dup2(in.pipes[in.i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (in.i < in.n_cmds - 1 && dup2(in.pipes[in.i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(in.pipes, in.n_cmds);
	if (curr->builtin_type != -1 && curr->builtin_type == 3)
	{
		line_env = ft_export(line_env, curr->cmd);
		exit(0);
	}
	cmd_args = ft_get_path(curr->cmd[0], env);
	if (!cmd_args)
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
	if (execve(cmd_args[0], curr->cmd, env) == -1)
	{
		(perror("execve failed"), ft_free_split(cmd_args), exit(1));
	}
}
