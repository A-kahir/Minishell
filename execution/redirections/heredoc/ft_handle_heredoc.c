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

#include "../../execution.h"

int ft_handle_heredoc(char *del)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
        (perror("pipe failed"), exit(1));
    if (!del)
    {
        fprintf(stderr, "heredoc: delimiter is NULL\n");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, del) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
