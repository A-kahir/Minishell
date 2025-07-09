/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:58:40 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/07 14:51:44 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = (char *)s;
	while (n > 0)
	{
		*(tmp++) = 0;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*t;

	t = malloc((count * size));
	if (!t)
		return (t);
	ft_bzero(t, (count * size));
	return (t);
}
// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

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


char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while(src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
	return (dest);
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

// char	*ft_strdup(const char *src)
// {
// 	char	*d;
// 	size_t	i;

// 	i = 0;
// 	d = (char *) malloc(ft_strlen(src) + 1);
// 	if (!d)
// 		return (0);
// 	while (*src)
// 		d[i++] = *src++;
// 	d[i] = '\0';
// 	return (d);
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	unsigned char	c1;
// 	unsigned char	c2;
// 	int				i;
// 	int				diff;

// 	i = 0;
// 	diff = 0;
// 	while (s2[i] || s1[i])
// 	{
// 		if (s1[i] != s2[i])
// 		{
// 			c1 = s1[i];
// 			c2 = s2[i];
// 			diff = c1 - c2;
// 			return (diff);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int token_len(char **tokens)
{
	int len = 0;
	while (tokens[len])
		len++;
	return len;
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

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i;
	size_t i2;

	i = 0;
	i2 = 0;
	while (s[i] != '\0')
	{
		i2 = 0;
		while (reject[i2] != '\0')
		{
			if (s[i] == reject[i2])
				return (i);
			i2++;
		}
		i++;
	}
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char **ft_subarray(char **tokens, int start, int end)
{
	char **sub = malloc(sizeof(char *) * (end - start + 1));
	int i = 0;
	while (start < end)
	{
		sub[i++] = ft_strdup(tokens[start++]);
	}
	sub[i] = NULL;
	return (sub);
}

char	*ft_substr_par(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	l1;
	size_t	i;

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


// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned char	c1;
// 	unsigned char	c2;
// 	size_t			i;
// 	int				diff;

// 	i = 0;
// 	diff = 0;
// 	if (n == 0)
// 		return (0);
// 	while ((s1[i] || s2[i]) && i < n)
// 	{
// 		if (s1[i] != s2[i])
// 		{
// 			c1 = s1[i];
// 			c2 = s2[i];
// 			diff = c1 - c2;
// 			return (diff);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
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

// static int	count_word(const char *str, char c)
// {
// 	int		i;
// 	int		j;
// 	size_t	f;

// 	i = 0;
// 	j = 0;
// 	f = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			j = 0;
// 		else if (j == 0)
// 		{
// 			j = 1;
// 			f++;
// 		}
// 		i++;
// 	}
// 	return (f);
// }

// static void	tfree(char **strs, int count)
// {
// 	while (count-- > 0)
// 		free(strs[count]);
// 	free(strs);
// }

// static char	**ft_loop(char **str, const char *s, char c)
// {
// 	size_t	u;
// 	int		strnum;
// 	int		i;
// 	int		countw;

// 	i = -1;
// 	u = 0;
// 	strnum = 0;
// 	countw = count_word(s, c);
// 	while (strnum < countw && u <= ft_strlen(s))
// 	{
// 		if (s[u] != c && i == -1)
// 			i = u;
// 		else if ((s[u] == c || u == ft_strlen(s)) && i >= 0)
// 		{
// 			str[strnum] = ft_substr(s, i, u - i);
// 			if (!str[strnum])
// 				return (tfree(str, strnum), NULL);
// 			strnum++;
// 			i = -1;
// 		}
// 		u++;
// 	}
// 	str[strnum] = NULL;
// 	return (str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**str;

// 	if (!s)
// 		return (NULL);
// 	str = malloc(sizeof(char *) * (count_word(s, c) + 1));
// 	if (!str)
// 		return (NULL);
// 	return (ft_loop(str, s, c));
// }
