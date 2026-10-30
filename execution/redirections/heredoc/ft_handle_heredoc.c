/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:02:30 by akahir            #+#    #+#             */
/*   Updated: 2025/05/31 14:02:30 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

static void	sig_heredoc(int signum)
{
	(void)signum;
	g_status = 4;
	close (0);
}

static void	ft_expand_write(char *line, t_built *env,
t_exec stat, int *pipe_fd)
{
	char	*tmp;

	if (stat.heredoc_flag_q == 0)
		tmp = expanding_heredoc(line, env, &stat);
	else
		tmp = ft_strdup(line, 0, 0);
	free(line);
	if (tmp)
	{
		write(pipe_fd[1], tmp, ft_strlen(tmp));
		write(pipe_fd[1], "\n", 1);
	}
}

static int	ft_readline_heredoc(char *del, t_built *line_env,
t_exec stat, int *pipe_fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		line = readline("> ");
		if (!line)
		{
			if (g_status == 3)
				write(1, "\033[1A\033[2C", 9);
			break ;
		}
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		ft_expand_write(line, line_env, stat, pipe_fd);
	}
	return (0);
}

int	ft_handle_heredoc(char *del, t_built *line_env, t_exec stat)
{
	int		pipe_fd[2];
	int		k;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	if (!del)
		return (write(2, "heredoc: delimiter is NULL\n", 28),
			close(pipe_fd[0]), close(pipe_fd[1]), -1);
	g_status = 3;
	k = dup(0);
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	ft_readline_heredoc(del, line_env, stat, pipe_fd);
	signal(SIGINT, SIG_IGN);
	if (dup2(k, 0) == -1)
		return (-1);
	if (g_status == 4)
		return (-1);
	return (close(pipe_fd[1]), pipe_fd[0]);
}
