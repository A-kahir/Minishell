/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:29:37 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 17:29:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

int ft_heredoc_after(t_data *data, t_built *line_env, t_ex_othr env_here)
{
    t_exec in;
    t_data *tmp;
    t_redir *redir;
    pid_t pid;
    int status;

    status = 0;
    in.n_cmds = ft_count_cmds(data);
    in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
    if (!in.pipes)
        exit(1);
    in.i = 0;
    while (in.i < in.n_cmds - 1)
    {
        if (pipe(in.pipes[in.i]) == -1)
            (perror("pipe failed"), exit(1));
        in.i++;
    }
    int *hered_fd = malloc(sizeof(int) * in.n_cmds);
    if (!hered_fd)
        exit(1);
    in.i = 0;
    tmp = data;
    while (in.i < in.n_cmds)
    {
        hered_fd[in.i] = -1;
        int fd = -1;
        redir = tmp->redir;
        while (redir)
        {
            if (redir->type == 3)
            {
                if (fd != -1)
                    close(fd);
                fd = ft_handle_heredoc(redir->target);
            }
            redir = redir->next;
        }
        if (fd != -1)
            hered_fd[in.i] = fd;

        tmp = tmp->next;
        in.i++;
    }
    in.status = (char *)hered_fd;
    t_data *curr = data;
    in.i = 0;
    while (curr)
    {
        pid = fork();
        if (pid == -1)
            (perror("fork failed"), ft_close_pipes(in.pipes, in.n_cmds), exit(1));
        else if (pid == 0)
            ft_child_hered_aft(curr, line_env, env_here, in);
        curr = curr->next;
        in.i++;
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        if (hered_fd[in.i] != -1)
            close(hered_fd[in.i]);
        in.i++;
    }
    while (wait(&status) > 0);
    status = status / 256;
    free(in.pipes);
    free(hered_fd);
    return (status);
}
