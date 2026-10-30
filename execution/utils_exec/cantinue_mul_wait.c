/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cantinue_mul_wait.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:38:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/27 16:58:49 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_data	*ft_get_last_cmd(t_data *tmp, t_exec in)
{
	int	j;

	j = 0;
	while (j < in.n_cmds - 1)
	{
		if (tmp && tmp->next)
			tmp = tmp->next;
		j++;
	}
	return (tmp);
}

int	ft_is_interactive_cmd(t_data *tmp)
{
	if (tmp && tmp->cmd && tmp->cmd[0])
		if (ft_strcmp(tmp->cmd[0], "top") == 0
			|| ft_strcmp(tmp->cmd[0], "wc") == 0)
			return (1);
	return (0);
}

void	ft_handle_sigint(int flag_interactive, int *signal_printed)
{
	if (!*signal_printed)
	{
		if (flag_interactive)
			write(1, "\n", 2);
		else
			write(1, "\n", 2);
		*signal_printed = 1;
	}
}
