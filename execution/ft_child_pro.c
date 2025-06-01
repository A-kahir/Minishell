/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:09:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:09:19 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_child_pro(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char	**cmd_args;

	if (i > 0 && dup2(pipes[i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(pipes, n_cmds);
	cmd_args = ft_get_path(curr->cmd[0], env);
	if (!cmd_args)
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(1));
	if (execve(cmd_args[0], curr->cmd, env) == -1)
	{
		(perror("execve failed"), exit(1));
	}
}
