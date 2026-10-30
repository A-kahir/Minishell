/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:19:26 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:28:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_substr(char *s, int start, size_t len)
{
	char	*ptr;
	size_t	alloc_size;

	if (s == NULL)
		return (NULL);
	if (s == NULL || start >= ft_strlen(s))
	{
		return (ft_strdup("", 0, 0));
	}
	alloc_size = ft_strlen(s) - start;
	if (alloc_size > len)
	{
		alloc_size = len;
	}
	ptr = malloc_cl((alloc_size + 1) * sizeof(char), ALLOCATE, 0);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(ptr, &s[start], alloc_size);
	ptr[alloc_size] = '\0';
	return (ptr);
}
