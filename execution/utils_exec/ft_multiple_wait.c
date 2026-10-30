/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_wait.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:08:48 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 12:13:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_handle_sigquit(int flag_interactive, int *signal_printed)
{
	if (!*signal_printed)
	{
		if (flag_interactive)
			write(1, "\n", 2);
		else
			write(1, "Quit: 3\n", 9);
		*signal_printed = 1;
	}
}

static int	ft_handle_signal(int status, t_pid *t,
int flag_interactive, int *signal_printed)
{
	int	sig;
	int	final_status;

	1 && (sig = WTERMSIG(status), final_status = 0);
	if (sig == SIGINT)
	{
		ft_handle_sigint(flag_interactive, signal_printed);
		if (t->ch_pid == t->last_pid)
			final_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_handle_sigquit(flag_interactive, signal_printed);
		if (t->ch_pid == t->last_pid)
			final_status = 131;
	}
	else
		if (t->ch_pid == t->last_pid)
			final_status = 128 + sig;
	return (final_status);
}

int	ft_multiple_wait(t_data *tmp, t_exec *in, int status, pid_t l_p)
{
	t_pid	t;
	int		final_status;
	int		signal_printed;
	int		flag_interactive;
	int		temp_status;

	1 && (tmp = ft_get_last_cmd(tmp, *in), final_status = 0);
	flag_interactive = ft_is_interactive_cmd(tmp);
	1 && (t.ch_pid = 1, signal_printed = 0, t.last_pid = l_p);
	while (t.ch_pid > 0)
	{
		1 && (t.ch_pid = wait(&status));
		if (isatty(0))
			tcsetattr(0, TCSANOW, &in->g_orig_term);
		if (WIFSIGNALED(status))
		{
			temp_status = ft_handle_signal(status, &t,
					flag_interactive, &signal_printed);
			if (temp_status != 0)
				final_status = temp_status;
		}
		else if (WIFEXITED(status) && t.ch_pid == t.last_pid)
			final_status = WEXITSTATUS(status);
	}
	return (final_status);
}
