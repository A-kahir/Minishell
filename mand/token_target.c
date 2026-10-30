/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_target.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/25 20:39:03 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*the_rightone(t_tokenize *t, char *str, t_built *env, t_exec *inn)
{
	char	*in;

	if (t->cha == '\"')
		in = expanding(ft_subpar(str, t->st, t->quote_len), env, inn);
	else
		in = ft_subpar(str, t->st, t->quote_len);
	return (in);
}

static int	norm_help(char *str, int *i)
{
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t')
		&& str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	return (*i);
}

static char	*et(char *str, t_tokenize *t)
{
	char	*tmp;

	tmp = ft_subpar(str, t->st, t->quote_len);
	return (tmp);
}

char	*extract_target(char *str, int i, t_built *env, t_exec *innn)
{
	char		*token;
	t_tokenize	t;

	token = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			t.st = i;
			t.cha = str[i++];
			while (str[i] && str[i] != t.cha)
				i++;
			if (str[i] == t.cha)
				i++;
			t.quote_len = i - t.st;
			token = ft_strjoin_par(token, the_rightone(&t, str, env, innn));
		}
		else
		{
			t.st = i;
			t.quote_len = norm_help(str, &i) - t.st;
			token = ft_strjoin_par(token, exp_target(et(str, &t), env, innn));
		}
	}
	return (token);
}

char	*extract_retoken(char *str, int i, t_built *env, t_exec *in)
{
	char		*token;
	t_tokenize	t;

	token = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			t.st = i;
			t.cha = str[i++];
			while (str[i] && str[i] != t.cha)
				i++;
			if (str[i] == t.cha)
				i++;
			t.quote_len = i - t.st;
			token = ft_strjoin_par(token, the_rightone(&t, str, env, in));
		}
		else
		{
			t.st = i;
			t.quote_len = norm_help(str, &i) - t.st;
			token = ft_strjoin_par(token, expanding(et(str, &t), env, in));
		}
	}
	return (token);
}
