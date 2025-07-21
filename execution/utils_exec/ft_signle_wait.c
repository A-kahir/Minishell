/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signle_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:48 by akahir            #+#    #+#             */
/*   Updated: 2025/07/21 11:46:17 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_signle_wait(int status, pid_t last_pid)
{
	pid_t ch_pid;
	int f_status = 0;
	while ((ch_pid = wait(&status)) > 0)
	{
		if (isatty(0))
			tcsetattr(0, TCSANOW, &g_orig_term);
		if (ch_pid == last_pid)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(1, "^C\n", 4);
					f_status = 128 + SIGINT;
				}
				else if(WTERMSIG(status) == SIGQUIT)
				{
					write(1, "^\\Quit: 3\n", 11);
					f_status = 128 + SIGQUIT;
				}
				else
				{
					f_status = 128 + WTERMSIG(status);
				}
			}
			else if (WIFEXITED(status))
			{
				f_status = WEXITSTATUS(status);
			}
		}
	}
	return (f_status);
}
