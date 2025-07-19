/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:58:40 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/19 18:21:17 by akahir           ###   ########.fr       */
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

char	**join_zmr(char *s1, char *s2) 
{
	int	i;
	char **t;

	i = 0;
	t = malloc(sizeof(char *) * 2);
	if(!t)
		return(NULL);
	if(!s1 )
		return NULL;
	t[0]= s1;
	t[1]= NULL;
	return (t);
}

int	count_zmr(char **s)
{
	int i;
	int	len;

	i = 0;
	len = 0;
	while(s[i])
	{
		len = len + ft_strlen(s[i]);
		i++;
	}
	return (len);
}

char    *ft_rejoin(int size, char **strs, char *sep)
{
    int        i;
    int        j;
    int        len;
    int        k;
    char    *s;

    len = ft_strlen(sep);
    k = 0;
    i = 0;
    s = malloc(sizeof(char) * (len + count_zmr(strs) + 1));
    while (i < size)
    {
        j = 0;
        while (strs[i][j])
            s[k++] = strs[i][j++];
        j = 0;
        while (sep[j] && i != size - 1)
            s[k++] = sep[j++];
        i++;
    }
    s[k] = '\0';
    return (s);
}

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

	if (!dest || !src)
		return (NULL);
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
	if (!tokens)
		return 0;
	int len = 0;
	while (tokens[len])
		len++;
	return len;
}

char    **ft_strjoinarray(char **s1, char **s2)
{
    char    **t;
    int        i;
    int        j;
    int        l1;
    int        l2;

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

static void	tfree(char **strs, int count)
{
	while (count-- > 0)
		free(strs[count]);
	free(strs);
}

char	*extract_token2(char *str, char c, int *i)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[*i] && str[*i] != c)
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
			while (str[*i] && str[*i] != c && str[*i] != '\"' && str[*i] != '\'')
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
		while (str[i] == c)
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
		while (str[i] == c)
			i++;
		if (!str[i])
			break ;
		tokens[j++] = extract_token2(str, c, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
