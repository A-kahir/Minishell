/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_read_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:55:40 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 12:05:25 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_exec_case(char **cmd_args, char **env)
{
	char	*args[3];

	args[0] = "/bin/sh";
	args[1] = cmd_args[0];
	args[2] = NULL;
	if (execve("/bin/sh", args, env) == -1)
	{
		perror("execve failed");
		ft_free_split(cmd_args);
		exit(1);
	}
}

static void	ft_exec_cmd(t_data *curr, t_ex_othr env_here)
{
	char	**cmd_args;

	if (!curr->cmd || !curr->cmd[0])
	{
		write(2, "minishell: ", 12);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, "command not found\n", 19);
		exit(127);
	}
	cmd_args = ft_get_path(curr->cmd[0], env_here.env);
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 12);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
	{
		if (errno == ENOEXEC)
			ft_exec_case(cmd_args, env_here.env);
		else
			(perror("execve failed"), ft_free_split(cmd_args), exit(1));
	}
}

static void	ft_execute_cmd(t_data *curr, t_built *line_env,
t_ex_othr env_here, t_exec in)
{
	char	*command;
	int		status;

	command = ft_check_built_cmd(curr);
	if (ft_strcmp(command, "built") == 0)
	{
		status = ft_is_builtins(curr, line_env, in);
		exit(status);
	}
	ft_exec_cmd(curr, env_here);
}

static void	ft_handle_pipes(t_data *curr, t_exec in)
{
	t_redir	*redir;
	int		have_input_redir;
	int		i;

	redir = curr->redir;
	if (in.n_cmds <= 1)
		return ;
	have_input_redir = 0;
	while (redir)
	{
		if (redir->type == READ_F)
		{
			have_input_redir = 1;
			break ;
		}
		redir = redir->next;
	}
	if (!have_input_redir && in.i > 0)
		dup2(in.pipes[in.i - 1][0], 0);
	if (in.i < in.n_cmds - 1)
		dup2(in.pipes[in.i][1], 1);
	i = 0;
	ft_close_pipes(in.pipes, in.n_cmds);
}

void	ft_child_read_f(t_data *curr, t_built *line_env,
t_ex_othr env_here, t_exec in)
{
	int				fd;

	if (isatty(0))
		tcgetattr(0, &in.g_orig_term);
	fd = ft_fd_redirections(curr, curr->redir);
	if (fd == 1)
		exit(1);
	if (!curr->cmd || !curr->cmd[0])
		exit(0);
	ft_handle_pipes(curr, in);
	ft_execute_cmd(curr, line_env, env_here, in);
}
