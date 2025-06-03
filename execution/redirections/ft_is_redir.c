/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 20:32:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, char **env, t_heredoc *heredoc)
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
        if (heredoc->after_hered == 1 && heredoc->before_hered == 0)
        {
            ft_heredoc_after(data, env);
        }
        else if (heredoc->before_hered == 1 && heredoc->after_hered == 0)
        {
           ft_heredoc_before(data, env);
        }
        else if (heredoc->middle_hered == 1)
        {
            printf("is meddle\n");
        }
    }
}


// int fd = ft_handle_heredoc(curr->redir->target);
//         int i = 0;
//         int flag_redir = ft_flag_redir(data);
// 	    int n_cmds = ft_count_cmds(data);
//         int		(*pipes)[2];
// 	    pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
//         while (i < n_cmds - 1)
// 		if (pipe(pipes[i++]) == -1)
// 			(perror("Pipe creation failed"), exit(1));
//         i = 0;
// 		while (i < n_cmds)
// 		{
// 			pid_t pid = fork();
// 			if (pid == -1)
// 				(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
// 			else if (pid == 0)
// 				ft_child_hered(data, pipes, i, n_cmds, fd, env);
// 			data = data->next;
// 			i++;
// 		}
// 		ft_close_pipes(pipes, n_cmds);
// 		while (wait(NULL) > 0);
// 		free(pipes);