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
    int status = 0;
    int has_input = 0;
    int has_output = 0;

    t_data *curr = data;
    while (curr)
    {
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == READ_F)
                has_input = 1;
            else if (redir->type == TRUNCATE || redir->type == APPEND)
                has_output = 1;
            redir = redir->next;
        }
        curr = curr->next;
    }
    if (env_here.heredoc->after_hered || env_here.heredoc->before_hered || env_here.heredoc->middle_hered)
        status = ft_is_heredoc(data, line_env, env_here, &status, stat);
    else if (has_input)
        status = ft_read_f(data, line_env, env_here);
    else if (has_output)
        status = ft_tran_app(data, line_env, env_here);

    return (status);
}
