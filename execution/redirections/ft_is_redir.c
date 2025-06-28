/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:28:48 by akahir           ###   ########.fr       */
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
                    ft_tran_app(data, curr, flag, env);
                }
                if (redir->type == 2)
                {
                    ft_read_f(data, curr, env);
                }
                if (redir->type == 3)
                {
                    if (heredoc->after_hered == 1)
                    {
                        ft_heredoc_after(data, env);
                    }
                    else if (heredoc->before_hered == 1)
                    {
                        ft_heredoc_before(data, env);
                    }
                    else if (heredoc->middle_hered == 1)
                    {
                        ft_handle_middle(data, env);
                    }
                }
                redir = redir->next;
            }
        }
        curr = curr->next;
    }
}
