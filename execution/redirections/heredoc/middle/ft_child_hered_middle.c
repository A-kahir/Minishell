/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_middle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:12 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 13:05:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_midd(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
    char **cmd_args;
    int hered_fd;
    int have_hered;
    
    if (!curr || !curr->cmd || !curr->cmd[0])
        exit(1);
    have_hered = 0;
    if (curr->redir && curr->redir->type == HEREDOC)
    {
        have_hered = 1;
        hered_fd = ft_handle_heredoc(curr->redir->target);
        if (hered_fd == -1)
            (write(2, "heredoc failed\n", 15), exit(1));
        if (dup2(hered_fd, 0) == -1)
            (perror("dup2 heredoc failed"), exit(1));
        close(hered_fd);
    }
    if (!have_hered && i > 0)
    {
        if (dup2(pipes[i - 1][0], 0) == -1)
            (perror("dup2 input failed"), exit(1));
    }
    if (i < n_cmds - 1)
    {
        if (dup2(pipes[i][1], 1) == -1)
            (perror("dup2 output failed"), exit(1));
    }
    ft_close_pipes(pipes, n_cmds);
    if (!curr->cmd || !curr->cmd[0])
        exit(0);
    cmd_args = ft_get_path(curr->cmd[0], env);
    if (!cmd_args)
        (printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
    if (execve(cmd_args[0], curr->cmd, env) == -1)
        (perror("execve failed"), exit(1));
}
