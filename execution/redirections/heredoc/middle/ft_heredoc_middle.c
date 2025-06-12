/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:34 by akahir            #+#    #+#             */
/*   Updated: 2025/06/10 18:15:15 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_handle_middle(t_data *data, char **env)
{
    int n_cmds = ft_count_cmds(data);
    int *hered_fd = malloc(sizeof(int) * n_cmds);
    if (!hered_fd)
        exit(1);
    
    // Process heredocs for each command
    t_data *tmp = data;
    int i = 0;
    while (i < n_cmds)
    {
        hered_fd[i] = -1;
        
        // Check all redirections for this command
        t_redir *redir = tmp->redir;
        while (redir)
        {
            if (redir->type == HEREDOC)
            {
                hered_fd[i] = ft_handle_heredoc(redir->target);
                break; // Only handle the first heredoc per command
            }
            redir = redir->next;
        }
        
        tmp = tmp->next;
        i++;
    }
    
    // Create pipes
    int (*pipes)[2] = malloc(sizeof(int[2]) * (n_cmds - 1));
    if (!pipes)
    {
        // Clean up heredoc fds before exiting
        for (int j = 0; j < n_cmds; j++)
        {
            if (hered_fd[j] != -1)
                close(hered_fd[j]);
        }
        free(hered_fd);
        exit(1);
    }
    
    i = 0;
    while (i < n_cmds - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("Pipe creation failed");
            // Clean up
            for (int j = 0; j < i; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            for (int j = 0; j < n_cmds; j++)
            {
                if (hered_fd[j] != -1)
                    close(hered_fd[j]);
            }
            free(pipes);
            free(hered_fd);
            exit(1);
        }
        i++;
    }
    
    // Fork and execute commands
    t_data *curr = data;
    i = 0;
    while (i < n_cmds)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            // Close all pipes created so far
            for (int k = 0; k < n_cmds - 1; k++)
            {
                close(pipes[k][0]);
                close(pipes[k][1]);
            }
            for (int j = 0; j < n_cmds; j++)
            {
                if (hered_fd[j] != -1)
                    close(hered_fd[j]);
            }
            free(pipes);
            free(hered_fd);
            exit(1);
        }
        else if (pid == 0)
        {
            ft_child_hered_midd(curr, pipes, i, n_cmds, hered_fd, env);
            // This should never be reached if execve succeeds
            exit(1);
        }
        curr = curr->next;
        i++;
    }
    
    // Parent process: close all pipes after all children are forked
    for (i = 0; i < n_cmds - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Close heredoc file descriptors in parent
    for (i = 0; i < n_cmds; i++)
    {
        if (hered_fd[i] != -1)
            close(hered_fd[i]);
    }
    
    // Wait for all children
    while (wait(NULL) > 0);
    
    // Clean up
    free(pipes);
    free(hered_fd);
}