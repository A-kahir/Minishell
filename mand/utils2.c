/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:33:16 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/23 13:42:31 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_par(char *s, int start, int len)
{
	char	*result;
	int		l1;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		l1 = ft_strlen(s) - start;
	else
		l1 = len;
	if (l1 == 0)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (l1 + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < l1 && i < ft_strlen(s))
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_par(char *s1, char *s2)
{
	char	*t;
	int		i;
	int		j;
	int		l1;
	int		l2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	t = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!t)
		return (NULL);
	while (i < l1)
		t[i++] = *s1++;
	while (j < l2)
		t[i + j++] = *s2++;
	t[i + j] = '\0';
	return (t);
}

char	*extract_token2(char *str, char c, int *i)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[*i] && str[*i] != c && str[*i] != '\t')
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
			while (str[*i] && str[*i] != c && str[*i] != '\t'
				&& str[*i] != '\"' && str[*i] != '\'')
				(*i)++;
			quote_len = *i - quote_start;
			in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return (token);
}

static int	count_word(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		free(extract_token2(str, c, &i));
		count++;
	}
	return (count);
}

char	**ft_split_par(char *str, char c)
{
	int		count;
	char	**tokens;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	count = count_word(str, c);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		f_clean(str);
	while (str[i])
	{
		while (str[i] == c || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		tokens[j++] = extract_token2(str, c, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
