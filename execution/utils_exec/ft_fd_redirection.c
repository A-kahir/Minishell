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

	while (redir)
	{
		if (redir->target && redir->target[0] == '$' && redir->target[1])
		{
			printf("minishell: %s: ambiguous redirect\n", redir->target);
			exit(1);
		}
		if (redir->type == 2)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
				(perror("dup2 infile"), exit(1));
			close(fd);
		}
		else if (redir->type == 0)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
				(perror("dup2 outfile"), exit(1));
			close(fd);
		}
		else if (redir->type == 1)
		{
			fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->target);
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
				(perror("dup2 appendfile"), exit(1));
			close(fd);
		}
		redir = redir->next;
	}
}

