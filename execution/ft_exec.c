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

static void ft_check_inf_outf(t_data *curr)
{
	int fd_inf;
	int fd_outf;

	if (curr->redir && (curr->redir->type == 0 || curr->redir->type == 3))
	{
		fd_inf = open_infile(curr->redir->target);
		if (dup2(fd_inf, 0) == -1)
			(perror("dup2 infile failed"), close(fd_inf), exit(1));
		close(fd_inf);
	}
	if (curr->redir && (curr->redir->type == 1 || curr->redir->type == 2))
	{
		fd_outf = open_outfiles(curr->redir->target, curr->redir->type == 2);
		if (dup2(fd_outf, 1) == -1)
			(perror("dup2 outfile failed"), close(fd_outf), exit(1));
		close(fd_outf);
	}
}

static void	ft_child_pro(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char	**cmd_args;

	if (i > 0 && dup2(pipes[i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(pipes, n_cmds);
	ft_check_inf_outf(curr);
	if (curr->redir && curr->redir->type == 3)
		ft_handle_heredoc(curr->redir->target);
	cmd_args = ft_get_path(curr->cmd[i], env);
	if (cmd_args && execve(cmd_args[0], cmd_args, env) == -1)
		(perror("execve failed"), exit(1));
}

void ft_exec(t_data *data, char **env)
{
	pid_t pid;
	int		(*pipes)[2];
	int i;

	if (data->type == 0)
	{
		int nb_cmd = ft_count_cmds(data->cmd);
		pipes = malloc(sizeof(int[2]) * (nb_cmd - 1));
		i = 0;
		while (i < nb_cmd - 1)
			if (pipe(pipes[i++]) == -1)
				(perror("Pipe creation failed"), exit(1));
		i = 0;
		while (i < nb_cmd)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(pipes, nb_cmd), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, pipes, i, nb_cmd, env);
			i++;
		}
		ft_close_pipes(pipes, nb_cmd);
		i = 0;
		while (i < nb_cmd)
		{
			wait(NULL);
			i++;
		}
	}
	else if (data->type == 1)
	{
		printf("************** HAVE A CMD *************\n");
		printf("data=> %s\n", data->cmd[0]);
	}
}
