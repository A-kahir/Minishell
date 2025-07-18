/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:13:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/18 12:33:09 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_child_redir(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
	char *command;
	char **cmd_args;
	int i;
	int fd;
	int has_output = 0;

	if (curr->redir)
	{
		fd = ft_fd_redirections(curr, curr->redir);
		if (fd == 1)
			exit(1);
		has_output = ft_has_output_redir(curr);
	}
	if (in.n_cmds > 1)
	{
		if (in.i > 0)
			dup2(in.pipes[in.i - 1][0], 0);
		if (in.i < in.n_cmds - 1 && has_output == 0)
			dup2(in.pipes[in.i][1], 1);
		i = 0;
		while (i < in.n_cmds - 1)
		{
			if (i != in.i - 1)
				close(in.pipes[i][0]);
			if (i != in.i)
				close(in.pipes[i][1]);
			i++;
		}
	}
	if (!curr->cmd || !curr->cmd[0])
		exit(0);
	command = ft_check_built_cmd(curr);
	if (ft_strcmp(command, "built") == 0)
	{
		ft_is_builtins(curr, line_env, in);
		exit(0);
	}
	cmd_args = ft_get_path(curr->cmd[0], env_here.env, line_env);
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 11);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	else if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
	{
		if (errno == ENOEXEC)
		{
			char *args[3];
			args[0] = "/bin/sh";
			args[1] = cmd_args[0];
			args[2] = NULL;
   			if (execve("/bin/sh", args, env_here.env) == -1)
				(perror("execve failed"), ft_free_split(cmd_args), exit(1));
			exit(127);
		}
		else
			(perror("execve failed"), ft_free_split(cmd_args), exit(1));
	}
}
