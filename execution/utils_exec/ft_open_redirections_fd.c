/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_redirections_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:28:27 by akahir            #+#    #+#             */
/*   Updated: 2025/07/29 18:56:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_have_in_redir(t_redir *redir, int found_hered, int *last_input)
{
	int		fd;
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == READ_F)
		{
			fd = open(curr->target, O_RDONLY);
			if (fd < 0)
				return (perror(curr->target), 1);
			if (!found_hered)
			{
				if (*last_input != -1)
					close(*last_input);
				*last_input = fd;
			}
			else
				close(fd);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_is_trunc(t_redir *redir, int *last_output)
{
	int		fd;
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == TRUNCATE)
		{
			fd = open(curr->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(curr->target), 1);
			if (*last_output != -1)
				close(*last_output);
			*last_output = fd;
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_is_app(t_redir *redir, int *last_output)
{
	int		fd;
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == APPEND)
		{
			if (*last_output != -1)
				close(*last_output);
			fd = open(curr->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				return (perror(curr->target), 1);
			*last_output = fd;
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_have_out_redir(t_redir *redir, int *last_output)
{
	if (ft_is_trunc(redir, last_output))
		return (1);
	if (ft_is_app(redir, last_output))
		return (1);
	return (0);
}
