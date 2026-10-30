/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:33:16 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/03 12:22:18 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_strdup(s2, 0, 0));
	if (!s2)
		return (ft_strdup(s1, 0, 0));
	i = 0;
	j = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	t = (char *)malloc_cl(sizeof(char) * (l1 + l2 + 1), ALLOCATE, 0);
	if (!t)
		return (NULL);
	while (i < l1)
		t[i++] = *s1++;
	while (j < l2)
		t[i + j++] = *s2++;
	t[i + j] = '\0';
	return (t);
}

static void	lesss(char *str, int *i)
{
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t')
		&& str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
}

char	*extract_token2(char *str, char c, int *i)
{
	char		*token;
	t_tokenize	t;

	token = NULL;
	while (str[*i] && str[*i] != c && str[*i] != '\t')
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
		extract_token2(str, c, &i);
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
	tokens = malloc_cl(sizeof(char *) * (count + 1), ALLOCATE, 0);
	if (!tokens)
		return (NULL);
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
