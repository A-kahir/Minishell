/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:34 by akahir            #+#    #+#             */
/*   Updated: 2025/07/09 17:18:13 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"
int ft_handle_middle(t_data *data, t_built *line_env, t_ex_othr env_here)
{
    t_exec in;
    t_data *curr;
    pid_t pid;
    int status;

    in.n_cmds = ft_count_cmds(data);
    if (in.n_cmds <= 0)
        return (0);
    in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
    if (!in.pipes)
        return (perror("malloc failed"), 1);
    in.i = 0;
    while (in.i < in.n_cmds - 1)
    {
        if (pipe(in.pipes[in.i]) == -1)
        {
            ft_close_pipes(in.pipes, in.i);
            free(in.pipes);
            return (perror("pipe creation failed"), 1);
        }
        in.i++;
    }
    int *hered_fd = malloc(sizeof(int) * in.n_cmds);
    if (!hered_fd)
        exit(1);
    in.i = 0;
    t_data *tmp = data;
    while (in.i < in.n_cmds)
    {
        hered_fd[in.i] = -1;
        int fd = -1;
        t_redir *redir = tmp->redir;
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
    curr = data;
    in.i = 0;
    while (in.i < in.n_cmds && curr)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_close_pipes(in.pipes, in.n_cmds);
            free(in.pipes);
            free(hered_fd);
            return (perror("Fork failed"), 1);
        }
        else if (pid == 0)
            ft_child_hered_midd(curr, line_env, env_here, in);
        curr = curr->next;
        in.i++;
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    while (wait(&status) > 0);
    status = status / 256;
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        if (hered_fd[in.i] != -1)
            close(hered_fd[in.i]);
        in.i++;
    }
    free(hered_fd);
    free(in.pipes);
    return (status);
}
