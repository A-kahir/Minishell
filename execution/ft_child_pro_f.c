/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_pro_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:15:06 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 22:25:51 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execution.h"

static void	ft_exec_cmd_f(t_data *curr, char **cmd_args, t_ex_othr env_here)
{
	char	*args[3];

	if (!cmd_args || !cmd_args[0])
	{
		write(2, "minishell: ", 12);
		write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	else if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
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

void	ft_child_pro_f(t_data *curr, t_built *line_env,
	t_ex_othr env_here, t_exec in)
{
	char	**cmd_args;
	int		flag_redir;
	char	*command;

	command = ft_check_built_redir(curr);
	flag_redir = ft_flag_redir(curr);
	if (in.i > 0 && dup2(in.pipes[in.i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (in.i < in.n_cmds - 1 && dup2(in.pipes[in.i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(in.pipes, in.n_cmds);
	if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		exit(ft_is_builtins_f(curr, line_env, in));
	if (flag_redir == 1)
		exit(ft_is_redir(curr, line_env, env_here, in));
	if (curr->cmd[0] == NULL)
		exit(0);
	cmd_args = ft_get_path_f(curr->cmd[0]);
	ft_exec_cmd_f(curr, cmd_args, env_here);
}
