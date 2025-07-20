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

static void handler(int signum)
{
    (void)signum;
    printf("\n");
    g_status = 4;
    close (0);
}

int ft_handle_heredoc(char *del, t_built *line_env, t_exec stat)
{
    int pipe_fd[2];
    char *line;
    char *expnd;
    char *tmp;
    int k = 0;
    
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
    if (pipe(pipe_fd) == -1)
        return (perror("pipe failed"), -1);
    if (!del)
    {
        write(2, "heredoc: delimiter is NULL\n", 28);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (-1);
    }
    int status = 0;
    g_status = 3;
    k = dup(0);
    while (1)
    {
        signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
        line = readline("> ");
        if (!line)
        {
            if (g_status == 3)
                write(1, "\033[1A\033[2C", 9); 
            break;
        }
        if (ft_strcmp(line, del) == 0)
        {
            free(line);
            break;
        }
        expnd = expanding(line, line_env, stat.last_cmd);
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
    if (dup2(k, 0) == -1)
        return (-1);
    if (g_status == 4)
        return (-1);
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
