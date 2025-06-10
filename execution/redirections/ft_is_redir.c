/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/10 18:08:19 by akahir           ###   ########.fr       */
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
            ft_handle_middle(data, env);
        }
    }
}
