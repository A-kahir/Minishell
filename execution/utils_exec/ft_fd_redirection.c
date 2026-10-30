/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:21:53 by akahir            #+#    #+#             */
/*   Updated: 2025/08/04 11:20:06 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_check_heredoc(t_redir *redir)
{
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	ft_check_to_open_f(t_redir *redir)
{
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (!curr->target)
		{
			write(2, "minishell: ", 12);
			if (curr->target)
				write(2, curr->target, 1);
			else
				write(2, "", 1);
			write(2, ": No such file or directory\n", 29);
			return (1);
		}
		if (curr->target[0] == '$' && curr->target[1] && curr->type != HEREDOC)
		{
			write(2, "minishell: ", 12);
			write(2, curr->target, ft_strlen(curr->target));
			write(2, ": ambiguous redirect\n", 22);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_dup_last_fds(int last_input, int last_output)
{
	if (last_input != -1)
	{
		if (dup2(last_input, 0) == -1)
			return (perror("dup2 infile"), 1);
		close(last_input);
	}
	if (last_output != -1)
	{
		if (dup2(last_output, 1) == -1)
			return (perror("dup2 outfile"), 1);
		close(last_output);
	}
	return (0);
}

int	ft_fd_redirections(t_data *data, t_redir *redir)
{
	int		last_input;
	int		last_output;
	int		found_hered;

	last_input = -1;
	last_output = -1;
	found_hered = ft_check_heredoc(redir);
	if (ft_check_to_open_f(redir))
		return (1);
	if (ft_open_redir(redir, found_hered, &last_input, &last_output))
		return (1);
	if (data->cmd)
		return (ft_dup_last_fds(last_input, last_output));
	return (0);
}
