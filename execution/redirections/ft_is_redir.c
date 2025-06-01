/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 20:32:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


void	ft_child_hered(t_data *curr, int pipes[][2], int i, int n_cmds, int fd, char **env)
{
	char	**cmd_args;

	if (dup2(fd, 0) == -1)
		(perror("dup2 input failed"), exit(1));
    close(fd);
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

void ft_is_redir(t_data *data, char **env)
{
    t_data *curr;
    
    curr = data;
    int flag = 0;
    while (curr)
    {
        if (curr->redir && curr->redir->type != -1)
        {
            if (curr == data)
                flag = 1;
            break;
        }
        curr = curr->next;
    }
    if (curr->redir->type == 0 || curr->redir->type == 1)
    {
        ft_tran_app(data, curr, flag, env);
    }
    else if (curr->redir->type == 2)
    {
        ft_read_f(data, curr, flag, env);
    }
    else if (curr->redir->type == 3)
    {
        int fd = ft_handle_heredoc(curr->redir->target);
        int i = 0;
        int flag_redir = ft_flag_redir(data);
	    int n_cmds = ft_count_cmds(data);
        int		(*pipes)[2];
	    pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
        while (i < n_cmds - 1)
		if (pipe(pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
        i = 0;
		while (i < n_cmds)
		{
			pid_t pid = fork();
			if (pid == -1)
				(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_hered(data, pipes, i, n_cmds, fd, env);
			data = data->next;
			i++;
		}
		ft_close_pipes(pipes, n_cmds);
		while (wait(NULL) > 0);
		free(pipes);
    }
}
