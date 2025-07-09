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

int ft_is_heredoc(t_data *data, t_built *line_env, t_ex_othr env_here, int *status, t_exec stat)
{
    if (env_here.heredoc->after_hered == 1)
    {
        printf("is after\n");
        *status = ft_heredoc_after(data, line_env, env_here, stat);
    }
    else if (env_here.heredoc->before_hered == 1)
    {
        printf("is before\n");
        *status = ft_heredoc_before(data, line_env, env_here, stat);
    }
    else if (env_here.heredoc->middle_hered == 1)
    {
        printf("is middle\n");
        *status = ft_handle_middle(data, line_env, env_here, stat);
    }
    return (*status);
}

int ft_is_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    t_data *curr;
    int status;
    int flag = 0;

    curr = data;
    status = 0;
    while (curr)
    {
        if (curr->redir)
        {
            t_redir *redir = curr->redir;
            while (redir)
            {
                if (redir->type == 0 || redir->type == 1)
                    status = ft_tran_app(curr, line_env, env_here);
                else if (redir->type == 2)
                    status = ft_read_f(curr, line_env, env_here);
                redir = redir->next;
            }
        }
        curr = curr->next;
    }
    ft_is_heredoc(data, line_env, env_here, &status, stat);
    // printf("status ==> %d\n", status);
    return (status);
}
