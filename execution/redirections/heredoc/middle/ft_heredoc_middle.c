/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:34 by akahir            #+#    #+#             */
/*   Updated: 2025/06/14 18:37:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_handle_middle(t_data *data, char **env)
{
    int n_cmds;
    int i;
    pid_t pid;
    int (*pipes)[2];
    t_data *curr;

    n_cmds = ft_count_cmds(data);
    if (n_cmds <= 0)
        return;
    pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
    if (!pipes)
        (perror("malloc failed"), exit(1));
    i = 0;
    while (i < n_cmds - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            ft_close_pipes(pipes, i);
            free(pipes);
            (perror("pipe creation failed"), exit(1));
        }
        i++;
    }
    curr = data;
    i = 0;
    while (i < n_cmds && curr)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_close_pipes(pipes, n_cmds);
            (free(pipes), perror("Fork failed"), exit(1));
        }
        else if (pid == 0)
            ft_child_hered_midd(curr, pipes, i, n_cmds, env);
        curr = curr->next;
        i++;
    }
    ft_close_pipes(pipes, n_cmds);
    while (wait(NULL) > 0);
    free(pipes);
}
