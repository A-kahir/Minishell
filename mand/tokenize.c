/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/13 00:24:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*extract_token(char *str, int *i)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[*i] && (str[*i] != ' ' || str[*i] == '\t') && !is_operator(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote_start = *i;
			cha = str[(*i)++];
			while (str[*i] && str[*i] != cha)
				(*i)++;
			if (str[*i] == cha)
				(*i)++;
			quote_len = *i - quote_start;
			in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
		else
		{
			quote_start = *i;
			while (str[*i] && (str[*i] != ' ' || str[*i] == '\t') && str[*i] != '\"'
				&& str[*i] != '\'' && !is_operator(str[*i]))
				(*i)++;
			quote_len = *i - quote_start;
			in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return (token);
}

char	*get_token(char *str, int *i)
{
	char	*op;

	while (str[*i] == ' ')
		(*i)++;
	if (is_operator(str[*i]))
	{
		if ((str[*i] == '<' && str[*i + 1] == '<')
			|| (str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '|' && str[*i + 1] == '|')
			|| (str[*i] == '&' && str[*i + 1] == '&'))
		{
			op = ft_substr_par(str, *i, 2);
			*i += 2;
			return (op);
		}
		else
		{
			op = ft_substr_par(str, *i, 1);
			(*i)++;
			return (op);
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
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		free(get_token(str, &i));
		count++;
	}
	return (count);
}

char	**tokenize(char *str)
{
	int		count;
	char	**tokens;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	count = count_tokens(str);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		f_clean(str);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		tokens[j++] = get_token(str, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
