/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:00:37 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 20:00:49 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	str = (unsigned char *)b;
	ch = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		str[i] = ch;
		i++;
	}
	return ((void *)str);
}
