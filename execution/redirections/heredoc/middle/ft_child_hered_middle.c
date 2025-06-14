/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_middle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:12 by akahir            #+#    #+#             */
/*   Updated: 2025/06/14 18:46:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_midd(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char **cmd_args;
	int hered_fd;
    
	hered_fd = ft_handle_heredoc(curr->redir->target);
	if (hered_fd == -1)
		(write(2, "fd failed\n", 11), exit(1));
	if (dup2(hered_fd, 0) == -1)
		(perror("dup2 heredoc failed"), exit(1));
	close(hered_fd);
	if (i > 0 && dup2(pipes[i - 1][0], 0) == -1)
		(perror("dup2 input failed"), exit(1));
	if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(pipes, n_cmds);
	cmd_args = ft_get_path(curr->cmd[0], env);
    printf("cmd_args ==> %s\n", cmd_args[0]);
	if (!cmd_args)
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(1));
	if (execve(cmd_args[0], curr->cmd, env) == -1)
		(perror("execve failed"), exit(1));
}


/*
     // 1. Setup input redirection
    if (hered_fd[i] != -1)
    {
        // This command has a heredoc, use heredoc input
        dup2(hered_fd[i], STDIN_FILENO);
    }
    else if (i > 0)
    {
        // Not first command and no heredoc, use pipe input
        dup2(pipes[i - 1][0], STDIN_FILENO);
    }
    // If first command and no heredoc, stdin remains unchanged (terminal input)

    // 2. Setup output redirection
    if (i < n_cmds - 1)
    {
        // Not last command, pipe output to next command
        dup2(pipes[i][1], STDOUT_FILENO);
    }
    // If last command, stdout remains unchanged (terminal output)

    // 3. Close all pipe file descriptors
    for (int j = 0; j < n_cmds - 1; ++j)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    // 4. Close all heredoc file descriptors
    for (int j = 0; j < n_cmds; ++j)
    {
        if (hered_fd[j] != -1)
            close(hered_fd[j]);
    }

    // 5. Handle other redirections (>, >>, <)
    t_redir *redir = curr->redir;
    while (redir)
    {
        if (redir->type == TRUNCATE)
        {
            int fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == APPEND)
        {
            int fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == READ_F)
        {
            int fd = open(redir->target, O_RDONLY);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        // HEREDOC is already handled above
        redir = redir->next;
    }

    // 6. Execute the command
    char **cmd_args = ft_get_path(curr->cmd[0], env);
    if (!cmd_args)
    {
        write(STDERR_FILENO, "minishell: ", 11);
        write(STDERR_FILENO, curr->cmd[0], strlen(curr->cmd[0]));
        write(STDERR_FILENO, ": command not found\n", 20);
        exit(127);
    }

    execve(cmd_args[0], curr->cmd, env);
    perror("execve failed");
    exit(126);
*/