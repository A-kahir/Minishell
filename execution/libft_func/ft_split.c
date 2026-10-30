/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:59:55 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:59:55 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static void	free_memory(size_t count)
{
	size_t	k;

	k = 0;
	while (k < count)
	{
		k++;
	}
}

static size_t	skip_delimiters(const char *s, size_t i, char c)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	handle_word(const char *s, size_t *i, char **ptr, char c)
{
	size_t	len_words;
	size_t	j;

	len_words = 0;
	if (s[*i] != c)
	{
		while (s[*i + len_words] && s[*i + len_words] != c)
			len_words++;
		*ptr = (char *)malloc_cl((len_words + 1) * sizeof(char), ALLOCATE, 0);
		if (!*ptr)
			return (0);
		j = 0;
		while (j < len_words)
		{
			(*ptr)[j] = s[*i + j];
			j++;
		}
		(*ptr)[j] = '\0';
		*i += len_words;
		return (1);
	}
	return (0);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	stock;

	if (s == NULL)
		return (NULL);
	ptr = (char **)malloc_cl((count_words(s, c) + 1) * sizeof(char *),
			ALLOCATE, 0);
	if (!ptr)
		return (NULL);
	i = skip_delimiters(s, 0, c);
	stock = 0;
	while (s[i])
	{
		if (handle_word(s, &i, &ptr[stock], c))
			stock++;
		else
		{
			free_memory(stock);
			return (NULL);
		}
		i = skip_delimiters(s, i, c);
	}
	ptr[stock] = NULL;
	return (ptr);
}
