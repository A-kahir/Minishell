/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_before.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:11:24 by akahir            #+#    #+#             */
/*   Updated: 2025/06/10 18:11:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

int ft_heredoc_before(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    t_exec in;
    t_data *curr;
    pid_t *pids;
    int status;
    int i;

    status = 0;
    in.n_cmds = ft_count_cmds(data);
    in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
    if (!in.pipes)
        return (1);
    i = 0;
    while (i < in.n_cmds - 1)
    {
        if (pipe(in.pipes[i]) == -1)
        {
            perror("Pipe creation failed");
            free(in.pipes);
            return (1);
        }
        i++;
    }
    int *hered_fd = malloc(sizeof(int) * in.n_cmds);
    if (!hered_fd)
    {
        free(in.pipes);
        return (1);
    }
    curr = data;
    i = 0;
    while (i < in.n_cmds)
    {
        hered_fd[i] = -1;
        int fd = -1;
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == 3)
            {
                if (fd != -1)
                    close(fd);
                fd = ft_handle_heredoc(redir->target, line_env, stat);
            }
            redir = redir->next;
        }
        if (fd != -1)
            hered_fd[i] = fd;
        curr = curr->next;
        i++;
    }
    in.status = (char *)hered_fd;
    pids = malloc(sizeof(pid_t) * in.n_cmds);
    if (!pids)
    {
        free(in.pipes);
        free(hered_fd);
        return (1);
    }
    curr = data;
    i = 0;
    while (i < in.n_cmds)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("Fork failed");
            ft_close_pipes(in.pipes, in.n_cmds);
            free(in.pipes);
            free(pids);
            free(hered_fd);
            return (1);
        }
        else if (pids[i] == 0)
        {
            ft_child_hered_bef(curr, line_env, env_here, in);
        }
        curr = curr->next;
        i++;
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    i = 0;
    while (i < in.n_cmds)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    status = status / 256;
    i = 0;
    while (i < in.n_cmds)
    {
        if (hered_fd[i] != -1)
            close(hered_fd[i]);
        i++;
    }
    free(in.pipes);
    free(pids);
    free(hered_fd);
    return (status);
}
