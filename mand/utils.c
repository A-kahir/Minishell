/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:58:40 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/23 13:40:53 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	int	i;

	i = 0;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		i = 1;
	}
	else
		i = 0;
	return (i);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	token_len(char **tokens)
{
	int	len;

	len = 0;
	if (!tokens)
		return (0);
	while (tokens[len])
		len++;
	return (len);
}

char	**ft_strjoinarray(char **s1, char **s2)
{
	char	**t;
	int		i;
	int		j;
	int		l1;
	int		l2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_subarray(s2, 0, token_len(s2)));
	if (!s2)
		return (ft_subarray(s1, 0, token_len(s1)));
	i = 0;
	j = 0;
	l1 = token_len(s1);
	l2 = token_len(s2);
	t = malloc(sizeof(char *) * (l1 + l2 + 1));
	if (!t)
		return (NULL);
	while (i < l1)
		t[i++] = ft_strdup(*s1++);
	while (j < l2)
		t[i + j++] = ft_strdup(*s2++);
	t[i + j] = NULL;
	return (t);
}

char	**ft_subarray(char **tokens, int start, int end)
{
	char	**sub;
	int		i;

	i = 0;
	sub = malloc(sizeof(char *) * (end - start + 1));
	while (start < end)
	{
		sub[i++] = ft_strdup(tokens[start++]);
	}
	sub[i] = NULL;
	return (sub);
}
