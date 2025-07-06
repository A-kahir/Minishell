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
		if (cur->cmd && cur->cmd[0])
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
		if (cur->cmd && cur->cmd[0])
		return (1);
		cur = cur->next;
	}
	return (0);
}

void    detect_heredoc_position(t_data *d, t_heredoc *h)
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

void    copy_array(char **dest, char **src, int len)
{
	int    i;
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

void    merge_cmd(t_data *a, t_data *b)
{
	char    **new;
	int        i;
	int        j;

	i = token_len(a->cmd);
	j = token_len(b->cmd);
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return ;
	copy_array(new, a->cmd, i);
	copy_array(new + i, b->cmd, j);
	new[i + j] = NULL;
	free(a->cmd);
	free(b->cmd);
	a->cmd = new;
	b->cmd = NULL;
}

void    merge_middle_heredoc_cmd(t_data *d)
{
	t_data    *cur;
	t_redir    *r;

	cur = d;
	while (cur && cur->next)
	{
		r = cur->redir;
		while (r)
		{
			if (r->type == HEREDOC && cur->next && cur->next->cmd)
				return (merge_cmd(cur, cur->next));
			r = r->next;
		}
		cur = cur->next;
	}
}
