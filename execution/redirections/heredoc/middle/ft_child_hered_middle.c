/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_middle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:12 by akahir            #+#    #+#             */
/*   Updated: 2025/06/10 18:12:20 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_midd(t_data *curr, int pipes[][2], int i, int n_cmds, int *hered_fd, char **env)
{
    if (i > 0)
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

    // 4. Execute the command
    char **cmd_args = ft_get_path(curr->cmd[0], env);
    if (!cmd_args)
    {
        fprintf(stderr, "minishell: %s: command not found\n", curr->cmd[0]);
        exit(127);
    }

    execve(cmd_args[0], curr->cmd, env);
    perror("execve failed");
    exit(126);
}