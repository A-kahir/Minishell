/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signle_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:48 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 12:06:06 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_take_status(int status)
{
	int	f_status;

	f_status = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 2);
			f_status = 128 + SIGINT;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit: 3\n", 9);
			f_status = 128 + SIGQUIT;
		}
		else
			f_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		f_status = WEXITSTATUS(status);
	return (f_status);
}

int	ft_signle_wait(int status, pid_t last_pid, t_exec *in)
{
	pid_t			ch_pid;
	int				f_status;

	f_status = 0;
	ch_pid = 1;
	while (ch_pid > 0)
	{
		ch_pid = wait(&status);
		if (isatty(0))
			tcsetattr(0, TCSANOW, &in->g_orig_term);
		if (ch_pid == last_pid)
		{
			f_status = ft_take_status(status);
		}
	}
	return (f_status);
}
