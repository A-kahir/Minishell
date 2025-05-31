/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:02:30 by akahir            #+#    #+#             */
/*   Updated: 2025/05/31 14:02:30 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_handle_heredoc(char *delimiter)
{
    int     pipe_fd[2];
    char    *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }
    while (1)
    {
        write(1, "> ", 2);
        line = readline(NULL);
        if (!line)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    if (dup2(pipe_fd[0], 0) == -1)
        (perror("dup2 heredoc failed"), exit(1));
    close(pipe_fd[0]);
}
