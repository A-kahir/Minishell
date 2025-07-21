/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_wait.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:08:48 by akahir            #+#    #+#             */
/*   Updated: 2025/07/21 12:09:16 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_multiple_wait(t_data *tmp, t_exec in, int status, pid_t last_pid)
{
	pid_t ch_pid;
	int final_status = 0;
	int signal_printed = 0;
	int j = 0;

	while (j < in.n_cmds - 1)
	{
		if (tmp && tmp->next)
			tmp = tmp->next;
		j++;
	}
	int flag_interactive = 0;
	if (tmp && tmp->cmd && tmp->cmd[0])
		if (ft_strcmp(tmp->cmd[0], "top") == 0 || ft_strcmp(tmp->cmd[0], "wc") == 0)
			flag_interactive = 1;
	while ((ch_pid = wait(&status)) > 0)
	{
		if (isatty(0))
			tcsetattr(0, TCSANOW, &g_orig_term);
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				if (!signal_printed)
				{
					if (flag_interactive)
						write(1, "\n", 1);
					else
						write(1, "^C\n", 3);
					signal_printed = 1;
				}
				if (ch_pid == last_pid)
					final_status = 130;
			}
			else if (sig == SIGQUIT)
			{
				if (!signal_printed)
				{
					if (flag_interactive)
						write(1, "^\\\n", 4);
					else
						write(1, "^\\Quit: 3\n", 11);
					signal_printed = 1;
				}
				if (ch_pid == last_pid)
					final_status = 131;
			}
			else
				if (ch_pid == last_pid)
					final_status = 128 + sig;
		}
		else if (WIFEXITED(status) && ch_pid == last_pid)
			final_status = WEXITSTATUS(status);
	}
	status = final_status;
	return (status);
}
