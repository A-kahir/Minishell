/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:09:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:54:43 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void ft_child_pro(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
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
		(ft_is_builtins(curr, line_env, in), exit(0));
	if (flag_redir == 1)
		(ft_is_redir(curr, line_env, env_here, in), exit(0));
	if (curr->cmd[0][0] == '$' && ft_check_this_var(curr->cmd[0] + 1, line_env) == 1)
		exit(0);
	t_data *tmp = curr;
	while (tmp)
	{
		int i = 0;
		while (tmp->cmd[i] != NULL)
		{
			free(tmp->cmd[i]);
			tmp->cmd[i] = ft_expanding_exec(tmp->cmd[i], line_env);
			i++;
		}
		tmp = tmp->next;
	}
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
