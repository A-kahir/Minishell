/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:21:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/12 15:42:53 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_fd_redirections(t_redir *redir)
{
    int fd;
    int last_input = -1;
    int last_output = -1;
    t_redir *current = redir;

    while (current)
    {
        if (!current->target || current->target[0] == '\0')
            return (1);
        if (current->target[0] == '$' && current->target[1])
        {
            write(2, "minishell: ", 12);
            write(2, current->target, ft_strlen(current->target));
            write(2, ": ambiguous redirect\n", 22);
            return (1);
        }
        if (current->type == READ_F)
        {
            if (last_input != -1)
                close(last_input);
            fd = open(current->target, O_RDONLY);
            if (fd < 0)
            {
                perror(current->target);
                return (1);
            }
            last_input = fd;
        }
        else if (current->type == TRUNCATE)
        {
            if (last_output != -1)
                close(last_output);
            fd = open(current->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(current->target);
                return (1);
            }
            last_output = fd;
        }
        else if (current->type == APPEND)
        {
            if (last_output != -1)
                close(last_output);
            fd = open(current->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(current->target);
                return (1);
            }
            last_output = fd;
        }
        current = current->next;
    }
    if (last_input != -1)
    {
        if (dup2(last_input, STDIN_FILENO) == -1)
        {
            perror("dup2 infile");
            return (1);
        }
        close(last_input);
    }
    if (last_output != -1)
    {
        if (dup2(last_output, STDOUT_FILENO) == -1)
        {
            perror("dup2 outfile");
            return (1);
        }
        close(last_output);
    }
    return (0);
}
