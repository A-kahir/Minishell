/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:34 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 18:35:47 by akahir           ###   ########.fr       */
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
    curr = data;
    in.i = 0;
    while (in.i < in.n_cmds && curr)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_close_pipes(in.pipes, in.n_cmds);
            free(in.pipes);
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
    free(in.pipes);
    return (status);
}
