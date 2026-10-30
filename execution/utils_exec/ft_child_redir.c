/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:13:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 23:42:52 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_child_redir_execve(t_data *curr, char **cmd_args, t_ex_othr env_here)
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
				(perror("execve failed"), ft_free_split(cmd_args), exit(1));
			exit(127);
		}
		else
			(perror("execve failed"), ft_free_split(cmd_args), exit(1));
	}
}

void	ft_child_redir_exec(t_data *curr, t_ex_othr env_here)
{
	char	**cmd_args;

	cmd_args = ft_get_path(curr->cmd[0], env_here.env);
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 11);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	ft_child_redir_execve(curr, cmd_args, env_here);
}

void	ft_child_redir_pipes(t_exec in, int has_output)
{
	int	i;

	i = 0;
	if (in.n_cmds > 1)
	{
		if (in.i > 0)
			dup2(in.pipes[in.i - 1][0], 0);
		if (in.i < in.n_cmds - 1 && has_output == 0)
			dup2(in.pipes[in.i][1], 1);
		while (i < in.n_cmds - 1)
		{
			if (i != in.i - 1)
				close(in.pipes[i][0]);
			if (i != in.i)
				close(in.pipes[i][1]);
			i++;
		}
	}
}

void	ft_child_redir(t_data *curr, t_built *line_env,
t_ex_othr env_here, t_exec in)
{
	char	*command;
	int		fd;
	int		has_output;

	fd = 0;
	has_output = 0;
	if (curr->redir)
	{
		fd = ft_fd_redirections(curr, curr->redir);
		if (fd == 1)
			exit(1);
		has_output = ft_have_output_redir(curr);
	}
	ft_child_redir_pipes(in, has_output);
	command = ft_check_built_cmd(curr);
	if (ft_strcmp(command, "built") == 0)
		exit(ft_is_builtins(curr, line_env, in));
	ft_child_redir_exec(curr, env_here);
}
