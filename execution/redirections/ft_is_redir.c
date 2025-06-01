/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 16:31:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, char **env)
{
    t_data *curr;
    
    curr = data;
    int flag = 0;
    while (curr)
    {
        if (curr->redir && curr->redir->type != -1)
        {
            if (curr == data)
                flag = 1;
            break;
        }
        curr = curr->next;
    }
    if (curr->redir->type == 0 || curr->redir->type == 1)
    {
        ft_tran_app(data, curr, flag, env);
    }
    else if (curr->redir->type == 2)
    {
        ft_read_f(data, curr, flag, env);
    }
    else if (curr->redir->type == 3)
    {
        int fd = ft_handle_heredoc(curr->redir->target);
        printf("fd===> %d\n", fd);
        if (fd == -1)
        {
            perror("heredoc");
            return ;
        }
        if (dup2(fd, 0) == -1)
        {
            perror("dup2 heredoc");
            close(fd);
            return ;
        }
        close(fd);
        char **cmd_args = ft_get_path(curr->cmd[0], env);
        if (!cmd_args)
        {
            printf("minishell: %s: command not found\n", curr->cmd[0]);
            return ;
        }
        if (execve(cmd_args[0], curr->cmd, env) == -1)
        {
            perror("execve failed");
            return ;
        }
    }
}
