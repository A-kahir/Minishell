/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:28:26 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/28 16:24:32 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*create_data_node(char **s)
{
	t_data	*node;

	node = malloc_cl(sizeof(t_data), ALLOCATE, 0);
	if (!node)
		return (NULL);
	node->type = find_pipe(s);
	node->redir = NULL;
	node->builtin_type = NOT_BUILTIN;
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}

t_data	*creatn(t_norm *norm, t_built *env, t_exec *in)
{
	t_data	*cmd;
	int		j;

	j = 0;
	cmd = create_data_node(norm->s);
	if (!cmd)
		return (malloc_cl(0, 2, 0), NULL);
	j = check_red(norm->s, norm->k, norm->i);
	if (j >= 0)
	{
		cmd->redir = creatn2(norm, env, in);
		cmd->cmd = command(norm->s, norm->k, norm->i);
	}
	else
	{
		cmd->cmd = ft_subarray(norm->s, norm->k, norm->i);
		cmd->redir = NULL;
	}
	return (cmd);
}

int	less_line(t_norm *n)
{
	if (!mp(n->s[n->i], "|") || !mp(n->s[n->i], "||") || !mp(n->s[n->i], "&&"))
	{
		return (0);
	}
	return (1);
}

t_data	*loop(t_norm *n, t_data *cmd, t_built *env, t_exec *in)
{
	t_less	nodes;

	1 && (nodes.curr = NULL, nodes.node = NULL);
	while (n->s[n->i])
	{
		if (!less_line(n))
		{
			nodes.curr = creatn(n, env, in);
			if (!cmd)
				cmd = nodes.curr;
			else
				nodes.node->next = nodes.curr;
			1 && (nodes.node = nodes.curr, n->k = n->i + 1);
		}
		n->i++;
	}
	if (n->k < n->i)
	{
		nodes.curr = creatn(n, env, in);
		if (!cmd)
			cmd = nodes.curr;
		else
			nodes.node->next = nodes.curr;
	}
	return (cmd);
}

t_data	*part1(char **s, t_built *env, t_exec *in)
{
	t_data	*cmd;
	t_norm	norm;

	norm.s = s;
	norm.i = 0;
	norm.k = 0;
	cmd = NULL;
	cmd = loop(&norm, cmd, env, in);
	return (cmd);
}
