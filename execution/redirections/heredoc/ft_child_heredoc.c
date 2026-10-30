/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:06:55 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 15:06:55 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void	ft_cantinue(t_data *curr, t_exec in)
{
	int	*hered_fd;

	hered_fd = (int *)in.status;
	if (hered_fd[in.i] != -1)
	{
		if (dup2(hered_fd[in.i], STDIN_FILENO) == -1)
			(perror("dup2"), exit(1));
		close(hered_fd[in.i]);
	}
	else if (in.i > 0)
		if (dup2(in.pipes[in.i - 1][0], STDIN_FILENO) == -1)
			(perror("dup2"), exit(1));
	if (ft_fd_redirections(curr, curr->redir) == 1)
		exit(1);
	if (!curr->cmd || !curr->cmd[0])
		exit(0);
	if (in.i < in.n_cmds - 1 && !ft_check_otp_redir(curr->redir))
	{
		if (dup2(in.pipes[in.i][1], STDOUT_FILENO) == -1)
			(perror("dup2"), exit(1));
	}
}

static void	ft_execute_cmd(t_data *curr, t_ex_othr env_here, char **cmd_args)
{
	char	*args[3];

	if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
	{
		if (errno == ENOEXEC)
		{
			args[0] = "/bin/sh";
			args[1] = cmd_args[0];
			args[2] = NULL;
			if (execve("/bin/sh", args, env_here.env) == -1)
				(perror("execve"), ft_free_split(cmd_args), exit(1));
			exit(127);
		}
		(perror("execve"), ft_free_split(cmd_args), exit(1));
	}
}

void	ft_child_heredoc(t_data *curr, t_built *line_env,
	t_ex_othr env_here, t_exec in)
{
	char	**cmd_args;
	char	*command;

	(ft_cantinue(curr, in), ft_close_pipes(in.pipes, in.n_cmds));
	command = ft_check_built_cmd(curr);
	if (ft_strcmp(command, "built") == 0)
		exit(ft_is_builtins(curr, line_env, in));
	if (curr->cmd[0][0] == '$' && line_env
		&& ft_check_this_var(curr->cmd[0] + 1, line_env) == 1)
		exit(0);
	cmd_args = ft_get_path(curr->cmd[0], env_here.env);
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 11);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		(write(2, ": command not found\n", 20), exit(127));
	}
	ft_execute_cmd(curr, env_here, cmd_args);
}
