/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specify_type_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:12:57 by akahir            #+#    #+#             */
/*   Updated: 2025/07/29 16:53:39 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_check_otp_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TRUNCATE || redir->type == APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	ft_have_heredoc(t_data *data)
{
	t_data	*curr;
	t_redir	*redir;

	curr = data;
	while (curr)
	{
		redir = curr->redir;
		while (redir)
		{
			if (redir->type == 3)
				return (1);
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_have_output_redir(t_data *data)
{
	t_data	*curr;
	t_redir	*redir;

	curr = data;
	while (curr)
	{
		redir = curr->redir;
		while (redir)
		{
			if (redir->type == 0 || redir->type == 1)
				return (1);
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_have_input_redir(t_data *data)
{
	t_data	*curr;
	t_redir	*redir;

	curr = data;
	while (curr)
	{
		redir = curr->redir;
		while (redir)
		{
			if (redir->type == 2)
				return (1);
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}
