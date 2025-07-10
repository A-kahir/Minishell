/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_after.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:57:34 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 17:57:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_aft(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
	char **cmd_args;
	int *hered_fd = (int *)in.status;
	char *command;

	if (curr->cmd[0] == NULL)
        exit(0);
	command = ft_check_built_cmd(curr);
	if (in.i == 0 && hered_fd[0] != -1)
	{
		if (dup2(hered_fd[0], 0) == -1)
			(perror("dup2 heredoc"), exit(1));
		close(hered_fd[0]);
	}
	else if (in.i > 0)
	{
		if (dup2(in.pipes[in.i - 1][0], 0) == -1)
			(perror("dup2 pipe input"), exit(1));
	}
	if (in.i < in.n_cmds - 1)
	{
		if (dup2(in.pipes[in.i][1], 1) == -1)
			(perror("dup2 pipe output"), exit(1));
	}
	ft_close_pipes(in.pipes, in.n_cmds);
	if (ft_strcmp(command, "built") == 0)
		(ft_is_builtins(curr, line_env, in), exit(0));
	if (curr->cmd[0][0] == '$' && ft_check_this_var(curr->cmd[0] + 1, line_env) == 1)
		exit(0);
	cmd_args = ft_get_path(curr->cmd[0], env_here.env, line_env);
	if (!cmd_args || !cmd_args[0])
	{
		if (curr->cmd[0] && curr->cmd[0][0] >= '0' && curr->cmd[0][0] <= '9')
		{
			write(2, "minishell: ", 11);
			write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
			write(2, ": command not found\n", 21);
			exit(127);
		}
		else
		{
			write(2, "minishell: ", 11);
			write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
			write(2, ": command not found\n", 21);
			exit(127);
		}
	}
	else if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
		(perror("execve failed"), ft_free_split(cmd_args), exit(1));
}
