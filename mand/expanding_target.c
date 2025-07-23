/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:43:15 by yael-oua            #+#    #+#             */
/*   Updated: 2025/06/30 15:43:15 by yael-oua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    has_cmd_before(t_data *d, int pos)
{
	int        i;
	t_data    *cur;

	cur = d;
	i = 0;
	while (cur && i < pos)
	{
		if ((cur->cmd && cur->cmd[0]) ||(cur->redir && cur->redir->target))
			return (1);
		cur = cur->next;
		i++;
	}
	return (0);
}

int    has_cmd_after(t_data *d, int pos)
{
	int        i;
	t_data    *cur;

	cur = d;
	i = 0;
	while (cur && i <= pos)
	{
		cur = cur->next;
		i++;
	}
	while (cur)
	{
		if ((cur->cmd && cur->cmd[0]) || (cur->redir && cur->redir->target))
		return (1);
		cur = cur->next;
	}
	return (0);
}

void    detect_heredoc_position_with_pipes(t_data *d, t_heredoc *h)
{
	t_data    *cur;
	t_redir    *r;
	int        pos;

	cur = d;
	h->before_hered = 0;
	h->middle_hered = 0;
	h->after_hered = 0;
	pos = 0;
	while (cur)
	{
		r = cur->redir;
		while (r && r->type != HEREDOC)
			r = r->next;
		if (r)
			break ;
		cur = cur->next;
		pos++;
	}
	if (!cur)
		return ;
	if ((pos == 0 || has_cmd_after(d, pos)) && !has_cmd_before(d, pos))
		h->after_hered = 1;
	else if (has_cmd_before(d, pos) && has_cmd_after(d, pos))
		h->middle_hered = 1;
	else if (has_cmd_before(d, pos) && !has_cmd_after(d, pos))
		h->before_hered = 1;
}
