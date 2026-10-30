/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:56:13 by akahir            #+#    #+#             */
/*   Updated: 2025/08/04 11:48:00 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_handle_output_redir(t_redir *curr, int *last_output)
{
	int	fd;

	if (curr->type == TRUNCATE)
	{
		fd = open(curr->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(curr->target), 1);
		if (*last_output != -1)
			close(*last_output);
		*last_output = fd;
	}
	else if (curr->type == APPEND)
	{
		fd = open(curr->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (perror(curr->target), 1);
		if (*last_output != -1)
			close(*last_output);
		*last_output = fd;
	}
	return (0);
}

int	ft_open_input_redir_sub(t_redir *redir, int found_hered, int *last_input)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (perror(redir->target), 1);
	if (!found_hered)
	{
		if (*last_input != -1)
			close(*last_input);
		*last_input = fd;
	}
	else
		close(fd);
	return (0);
}

int	ft_open_redir(t_redir *redir, int found_hered,
int *last_input, int *last_output)
{
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == TRUNCATE || curr->type == APPEND)
		{
			if (ft_handle_output_redir(curr, last_output) != 0)
				return (1);
		}
		else if (curr->type == READ_F)
		{
			if (ft_open_input_redir_sub(curr, found_hered, last_input))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}
