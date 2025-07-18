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

int ft_has_heredoc(t_data *data)
{
    t_data *curr = data;
    while (curr)
    {
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == HEREDOC)
                return (1);
            redir = redir->next;
        }
        curr = curr->next;
    }
    return (0);
}

int ft_has_output_redir(t_data *data)
{
    t_data *curr = data;
    while (curr)
    {
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == TRUNCATE || redir->type == APPEND)
                return (1);
            redir = redir->next;
        }
        curr = curr->next;
    }
    return (0);
}

int ft_has_input_redir(t_data *data)
{
    t_data *curr = data;
    while (curr)
    {
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == READ_F)
                return (1);
            redir = redir->next;
        }
        curr = curr->next;
    }
    return (0);
}

int ft_is_heredoc(t_data *data, t_built *line_env, t_ex_othr env_here, int *status, t_exec stat)
{
    if (env_here.heredoc->after_hered)
        *status = ft_heredoc_after(data, line_env, env_here, stat);
    else if (env_here.heredoc->before_hered)
        *status = ft_heredoc_before(data, line_env, env_here, stat);
    else if (env_here.heredoc->middle_hered)
        *status = ft_handle_middle(data, line_env, env_here, stat);
    return (*status);
}

int ft_is_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    int status = 0;

    if (ft_has_heredoc(data) && 
        (env_here.heredoc->after_hered || 
         env_here.heredoc->before_hered || 
         env_here.heredoc->middle_hered))
        return ft_is_heredoc(data, line_env, env_here, &status, stat);
    if (ft_has_input_redir(data))
        return ft_read_f(data, line_env, env_here);
    if (ft_has_output_redir(data))
        return ft_tran_app(data, line_env, env_here, stat);
    return 0;
}


/*
		
int ft_is_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
	t_data *curr = data;
	int status = 0;

	while (curr)
	{
		t_redir *redir = curr->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (!curr->cmd || !curr->cmd[0])
				{
					redir = redir->next;
					continue;
				}
				if (env_here.heredoc->after_hered)
					status = ft_heredoc_after(data, line_env, env_here, stat);
				else if (env_here.heredoc->before_hered)
					status = ft_heredoc_before(data, line_env, env_here, stat);
				else if (env_here.heredoc->middle_hered)
					status = ft_handle_middle(data, line_env, env_here, stat);
			}
			else if (redir->type == READ_F)
			{
				if (!curr->cmd || !curr->cmd[0])
				{
					redir = redir->next;
					continue;
				}
				status = ft_read_f(data, line_env, env_here);
			}
			else if (redir->type == TRUNCATE || redir->type == APPEND)
			{
				status = ft_tran_app(data, line_env, env_here, stat);
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return status;
}

*/
