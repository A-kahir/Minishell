/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tran_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 19:48:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


void ft_create_pipes(t_exec *in)
{
	in->i = 0;
	while (in->i < in->n_cmds - 1)
	{
		if (pipe(in->pipes[in->i]) == -1)
		{
			perror("pipe creation failed");
			free(in->pipes);
			exit(1);
		}
		in->i++;
	}
}
void ft_fork_and_execute(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec *in)
{
	t_data *tmp;
	pid_t pid;
	int i;

	tmp = data;
	in->i = 0;
	while (in->i < in->n_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_close_pipes(in->pipes, in->n_cmds - 1);
			perror("fork failed");
			free(in->pipes);
			exit(1);
		}
		if (pid == 0)
			ft_child_redir(tmp, line_env, env_here, *in);
		tmp = tmp->next;
		in->i++;
	}
	i = 0;
	while (i < in->n_cmds - 1)
	{
		close(in->pipes[i][0]);
		close(in->pipes[i][1]);
		i++;
	}
}
int ft_tran_app(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    int status;
    t_exec in;
    t_data *curr = data;

    in.n_cmds = ft_count_cmds(data);
    if (curr->cmd == NULL && curr->redir && curr->redir->target)
    {
        int fd = ft_fd_redirections(curr->redir);
        if (fd == 1)
            return 1;
        write(1, "", 0);
        return 0;
    }

    if (in.n_cmds > 1)
    {
        in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
        if (!in.pipes)
        {
            perror("pipes");
            exit(1);
        }
        ft_create_pipes(&in);
        ft_fork_and_execute(data, line_env, env_here, &in);
        ft_close_pipes(in.pipes, in.n_cmds - 1);
        free(in.pipes);
    }
    else
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(1);
        }
        if (pid == 0)
        {
            ft_child_redir(curr, line_env, env_here, in);
            exit(0);
        }
    }

    while (wait(&status) > 0)
        ;
    status = status / 256;
    return status;
}
