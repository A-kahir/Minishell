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

int ft_handle_heredoc(char *del, t_built *line_env, t_exec stat)
{
    int pipe_fd[2];
    char *line;
    char *expnd;
    char *tmp;
    
    if (pipe(pipe_fd) == -1)
        return (perror("pipe failed"), -1);
    if (!del)
    {
        write(2, "heredoc: delimiter is NULL\n", 28);
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
        expnd = expanding(line, line_env);
        tmp = ft_expand_dollar(expnd, stat.status);
        free(expnd);
        if (tmp)
        {
            write(pipe_fd[1], tmp, ft_strlen(tmp));
            write(pipe_fd[1], "\n", 1);
            free(tmp);
        }
        free(line);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
