/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/27 15:15:30 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lesss(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '\"' && str[*i] != '\'' && !is_o(str[*i]))
		(*i)++;
}

char	*extract_token(char *str, int *i)
{
	char		*token;
	t_tokenize	t;

	token = NULL;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && !is_o(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			t.st = *i;
			t.cha = str[(*i)++];
			while (str[*i] && str[*i] != t.cha)
				(*i)++;
			if (str[*i] == t.cha)
				(*i)++;
			token = ft_strjoin_par(token, ft_subpar(str, t.st, *i - t.st));
		}
		else
		{
			t.st = *i;
			lesss(str, i);
			token = ft_strjoin_par(token, ft_subpar(str, t.st, *i - t.st));
		}
	}
	return (token);
}

static int	less_lines(char *str, int *i)
{
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '|' && str[*i + 1] == '|')
		|| (str[*i] == '&' && str[*i + 1] == '&'))
		return (1);
	return (0);
}

char	*get_token(char *str, int *i)
{
	char	*op;

	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (is_o(str[*i]))
	{
		if (str[*i] == '>' && str[*i + 1] == '|')
		{
			op = ft_subpar(str, *i, 1);
			*i += 2;
			return (op);
		}
		if (less_lines(str, i))
		{
			op = ft_subpar(str, *i, 2);
			return (*i += 2, op);
		}
		else
		{
			op = ft_subpar(str, *i, 1);
			return ((*i)++, op);
		}
	}
	return (extract_token(str, i));
}

int	count_tokens(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		get_token(str, &i);
		count++;
	}
	return (count);
}
