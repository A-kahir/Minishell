/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/05 13:36:46 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*extract_token(char *str, int *i, t_built *env)
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
			if(cha == '\"')
				in = expanding(ft_substr_par(str, quote_start, quote_len), env);
			else
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
			in = expanding(ft_substr_par(str, quote_start, quote_len), env);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return (token);
}

char	*get_token(char *str, int *i, t_built *env)
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
	return (extract_token(str, i, env));
}

int	count_tokens(char *str, t_built *env)
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
		free(get_token(str, &i, env));
		count++;
	}
	return (count);
}

char	**tokenize(char *str, t_built *env)
{
	int		count;
	char	**tokens;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	count = count_tokens(str, env);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		f_clean(str);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		tokens[j++] = get_token(str, &i, env);
	}
	tokens[j] = NULL;
	return (tokens);
}
