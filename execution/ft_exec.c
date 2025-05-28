/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:35:04 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 20:48:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_child_pro(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char	**cmd_args;

	if (i > 0 && dup2(pipes[i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(pipes, n_cmds);
	cmd_args = ft_get_path(curr->cmd[0], env);
	printf("cmd_args=> %s\n", cmd_args[0]);
	printf("cmd_args=> %s\n", cmd_args[1]);
	if (execve(cmd_args[0], curr->cmd, env))
		(perror("execve failed"), exit(1));
	else if (!cmd_args)
	{
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(1));
	}
}

void ft_exec(t_data *data, char **env)
{
	int		n_cmds;
	int		i;
	pid_t	pid;
	int		(*pipes)[2];

	i = 0;
	n_cmds = ft_count_cmds(data);
	pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
	while (i < n_cmds - 1)
		if (pipe(pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	if (data->type == 0)
	{
		i = 0;
		while (i < n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, pipes, i, n_cmds, env);
			data = data->next;
			i++;
		}
		ft_close_pipes(pipes, n_cmds);
		while (wait(NULL) > 0);
		free(pipes);
	}
	else if (data->type == 1)
	{
		char *command = ft_check_built_redir(data, 0);
		if (command == NULL)
		{
			i = 0;
			while (i < n_cmds)
			{
				pid = fork();
				if (pid == -1)
					(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
					ft_child_pro(data, pipes, i, n_cmds, env);
				data = data->next;
				i++;
			}
			ft_close_pipes(pipes, n_cmds);
			while (wait(NULL) > 0);
			free(pipes);
		}
		else if (data->builtin_type != -1)
		{
			ft_is_builtins(data, env);
		}
		else if (data->redir->type != -1)
		{
			ft_is_redir(data, env);
		}
	}
}
