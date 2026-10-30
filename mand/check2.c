/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:27:53 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/25 18:59:00 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (quote);
		}
		i++;
	}
	return (0);
}

int	check_before(char *s)
{
	int	i;

	if (!s)
		return (1);
	if (check_unclosed_quotes(s))
	{
		i = check_unclosed_quotes(s);
		write(2, "minishell: unexpected EOF while looking for matching `", 55);
		write(2, &i, 1);
		write(2, "'\n", 3);
		write(2, "minishell: syntax error: unexpected end of file\n", 49);
		return (1);
	}
	return (0);
}

int	mp(char *s1, char *s2)
{
	size_t	i;

	if (!s1)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_o(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	semiflag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
