/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:21:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/12 11:55:49 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

void ft_fd_redirections(t_redir *redir)
{
	int fd;
	int last_input;
	int last_output;

	last_input = -1;
	last_output = -1;
	while (redir)
	{
		if (redir->target && redir->target[0] == '$' && redir->target[1])
		{
			printf("minishell: %s: ambiguous redirect\n", redir->target);
			exit(1);
		}
		if (redir->type == 2)
		{
			if (last_input != -1)
				close(last_input);
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			last_input = fd;
		}
		else if (redir->type == 0)
		{
			if (last_output != -1)
				close(last_output);
			fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			last_output = fd;
		}
		else if (redir->type == 1)
		{
			if (last_output != -1)
				close(last_output);
			fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			last_output = fd;
		}
		redir = redir->next;
	}
	if (last_input != -1)
	{
		if (dup2(last_input, STDIN_FILENO) == -1)
			(perror("dup2 infile"), exit(1));
		close(last_input);
	}
	if (last_output != -1)
	{
		if (dup2(last_output, STDOUT_FILENO) == -1)
			(perror("dup2 outfile"), exit(1));
		close(last_output);
	}
}