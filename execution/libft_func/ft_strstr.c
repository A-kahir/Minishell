/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:40:06 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 14:28:45 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!haystack || !needle)
		return (1);
	if (!*needle)
		return (0);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (0);
		i++;
	}
	return (1);
}
