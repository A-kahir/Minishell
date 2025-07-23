/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:21:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/23 16:45:27 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_fd_redirections(t_data *data, t_redir *redir)
{
    int fd;
    int last_input = -1;
    int last_output = -1;
    t_redir *curr = redir;
    int heredoc_found = 0;

    while (curr)
    {
        if (curr->type == HEREDOC)
        {
            heredoc_found = 1;
            break;
        }
        curr = curr->next;
    }
    curr = redir;
    while (curr)
    {
        if (!curr->target || curr->target[0] == '\0')
        {
            write(2, "minishell: ", 12);
            if (curr->target)
                write(2, curr->target, 1);
            else
                write(2, "", 1);
            write(2, ": No such file or directory\n", 29);
            return (1);
        }
        if (curr->target[0] == '$' && curr->target[1] && curr->type != HEREDOC)
        {
            write(2, "minishell: ", 12);
            write(2, curr->target, ft_strlen(curr->target));
            write(2, ": ambiguous redirect\n", 22);
            return (1);
        }
        if (curr->type == READ_F)
        {
            fd = open(curr->target, O_RDONLY);
            if (fd < 0)
                return (perror(curr->target), 1);
            if (!heredoc_found)
            {
                if (last_input != -1)
                    close(last_input);
                last_input = fd;
            }
            else
                close(fd);
        }
        else if (curr->type == TRUNCATE)
        {
            if (last_output != -1)
                close(last_output);
            fd = open(curr->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0)
                return (perror(curr->target), 1);
            last_output = fd;
        }
        else if (curr->type == APPEND)
        {
            if (last_output != -1)
                close(last_output);
            fd = open(curr->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd < 0)
                return (perror(curr->target), 1);
            last_output = fd;
        }
        curr = curr->next;
    }
    if (data->cmd)
    {
        if (last_input != -1)
        {
            if (dup2(last_input, 0) == -1)
                return (perror("dup2 infile"), 1);
            close(last_input);
        }
        if (last_output != -1)
        {
            if (dup2(last_output, 1) == -1)
                return (perror("dup2 outfile"), 1);
            close(last_output);
        }
    }
    return (0);
}
