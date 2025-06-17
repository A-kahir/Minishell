/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/14 18:07:08 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, char **env, t_heredoc *heredoc)
{
    t_data *curr;
    int flag;

    curr = data;
    while (curr)
    {
        if (curr == data)
            flag = 1;
        else
            flag = 0;
        if (curr->redir)
        {
            t_redir *redir = curr->redir;
            while (redir)
            {
                if (redir->type == 0 || redir->type == 1)
                {
                    printf("tran or app\n");
                    ft_tran_app(data, curr, flag, env);
                }
                if (redir->type == 2)
                {
                    printf("read file\n");
                    ft_read_f(data, curr, flag, env);
                }
                if (redir->type == 3)
                {
                    if (heredoc->after_hered == 1)
                    {
                        printf("heredoc is after\n");
                        ft_heredoc_after(data, env);
                    }
                    else if (heredoc->before_hered == 1)
                    {
                        printf("heredoc is before\n");
                        ft_heredoc_before(data, env);
                    }
                    else if (heredoc->middle_hered == 1)
                    {
                        printf("heredoc is middle\n");
                        ft_handle_middle(data, env);
                    }
                }
                redir = redir->next;
            }
        }
        curr = curr->next;
    }
}
