/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:52:03 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    t_data *curr;
    int flag;

    curr = data;
    while (curr)
    {
        if (curr->redir)
        {
            t_redir *redir = curr->redir;
            while (redir)
            {
                if (redir->type == 0 || redir->type == 1)
                {
                    ft_tran_app(data, line_env, env_here, stat);
                }
                if (redir->type == 2)
                {
                    ft_read_f(data, curr, env_here.env);
                }
                if (redir->type == 3)
                {
                    if (env_here.heredoc->after_hered == 1)
                    {
                        ft_heredoc_after(data, env_here.env);
                    }
                    else if (env_here.heredoc->before_hered == 1)
                    {
                        ft_heredoc_before(data, env_here.env);
                    }
                    else if (env_here.heredoc->middle_hered == 1)
                    {
                        ft_handle_middle(data, env_here.env);
                    }
                }
                redir = redir->next;
            }
        }
        curr = curr->next;
    }
}
