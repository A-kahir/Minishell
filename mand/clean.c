/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:53:01 by yael-oua          #+#    #+#             */
/*   Updated: 2025/06/26 20:15:33 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    f_clean(char *s)
{
	if (s)
		free(s);
	printf("exit\n");
	exit(0);
}

void free_redir(t_redir *redir)
{
	t_redir *tmp;
	while (redir)
	{
		tmp = redir->next;
		if (redir->target)
			free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	freedp(char **s)
{
	int	i;
	int	k;

	if (!s)
		return ;
	i = token_len(s);
	k = 0;
	while (k < i)
	{
		free(s[k]);
		k++;
	}
	free(s);
}

void freenod(t_data *n)
{
	if (!n)
		return;
	if (n->cmd)
		freedp(n->cmd);
	if (n->redir)
		free_redir(n->redir);
	free(n);
	n = NULL;
}

void	n_clean(t_data *n)
{
	t_data	*t;

	while(n)
	{
		t = n->next;
		freenod(n);
		n = t;
	}
}
