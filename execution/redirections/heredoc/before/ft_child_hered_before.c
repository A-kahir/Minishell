/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_before.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:20:52 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 18:20:52 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_bef(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
	char **cmd_args;
	int heredoc_fd = -1;
	char *command;

	if (curr->redir && curr->redir->type == HEREDOC)
	{
		heredoc_fd = ft_handle_heredoc(curr->redir->target);
		if (heredoc_fd != -1)
		{
			if (dup2(heredoc_fd, STDIN_FILENO) == -1)
				(perror("dup2 input from heredoc failed"), exit(1));
			close(heredoc_fd);
		}
	}
	else if (in.i > 0)
	{
		if (dup2(in.pipes[in.i - 1][0], STDIN_FILENO) == -1)
			(perror("dup2 input from pipe failed"), exit(1));
	}
	if (in.i < in.n_cmds - 1)
	{
		if (dup2(in.pipes[in.i][1], STDOUT_FILENO) == -1)
			(perror("dup2 output to pipe failed"), exit(1));
	}
	ft_close_pipes(in.pipes, in.n_cmds);
	command = ft_check_built_cmd(curr);
	if (ft_strcmp(command, "built") == 0)
	{
		ft_is_builtins(curr, line_env, in);
		exit(0);
	}
	if (!curr->cmd || !curr->cmd[0])
		exit(0);
	cmd_args = ft_get_path(curr->cmd[0], env_here.env);
	if (!cmd_args)
	{
		if (curr->cmd[0][0] >= '0' && curr->cmd[0][0] <= '9')
			(printf("%s: command not found\n", curr->cmd[0]), exit(127));
		else
			(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
	}
	if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
		(perror("execve failed"), exit(1));
}
