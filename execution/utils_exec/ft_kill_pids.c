/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_pids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:56:00 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 19:48:46 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_kill_p(t_pid_list *head)
{
	t_pid_list	*temp;
	t_pid_list	*next;
	int			status;

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		next = temp->next;
		if (temp->pid > 1)
		{
			if (kill(temp->pid, 0) == 0)
			{
				if (kill(temp->pid, SIGKILL) == -1)
					perror("kill");
				else
					waitpid(temp->pid, &status, 0);
			}
		}
		temp = next;
	}
}
