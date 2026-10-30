/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:42 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/27 15:15:37 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pipe(char **s)
{
	int			i;
	t_type_node	t;
	int			c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			c++;
		if (!ft_strcmp(s[i], "<<"))
		{
			c = 0;
			t = 1;
			return (t);
		}
		i++;
	}
	if (c)
		t = 0;
	else
		t = 1;
	return (t);
}

static int	norm_help(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

char	*extract_quoates(char *str, int i)
{
	char		*token;
	t_tokenize	t;

	token = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			t.cha = str[i++];
			t.st = i;
			while (str[i] && str[i] != t.cha)
				i++;
			token = ft_strjoin_par(token, ft_subpar(str, t.st, i - t.st));
			if (str[i] == t.cha)
				i++;
		}
		else
		{
			t.st = i;
			i = norm_help(str, i);
			token = ft_strjoin_par(token, ft_subpar(str, t.st, i - t.st));
		}
	}
	return (token);
}

t_redir	*create_redir_node(t_type_redir type,
	char *target, t_built *env, t_exec *in)
{
	t_redir	*new;

	new = malloc_cl(sizeof(t_redir), ALLOCATE, 0);
	if (!new || !target)
		return (NULL);
	new->type = type;
	in->heredoc_flag_q = 0;
	if (type == HEREDOC)
	{
		if (semiflag(target))
		{
			new->target = extract_quoates(target, 0);
			in->heredoc_flag_q = 1;
		}
		else
			new->target = ft_strdup(target, 0, 0);
	}
	else if (semiflag(target))
		new->target = extract_quoates(extract_target(target, 0, env, in), 0);
	else
		new->target = exp_target(target, env, in);
	if (!new->target)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_type_redir	check_redirection(char *token)
{
	if (!token || !*token)
		return (NOT_REDIR);
	if (!ft_strcmp(token, ">"))
		return (TRUNCATE);
	if (!ft_strcmp(token, ">>"))
		return (APPEND);
	if (!ft_strcmp(token, "<"))
		return (READ_F);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	return (NOT_REDIR);
}
