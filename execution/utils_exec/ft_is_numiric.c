/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_numiric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:22:40 by akahir            #+#    #+#             */
/*   Updated: 2025/08/04 12:47:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_num_core(const char *str, int i, unsigned long long max)
{
	unsigned long long	result;

	result = 0;
	while (ft_is_digit(str[i]))
	{
		if (result > (max - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str[i] == '\0');
}

int	ft_is_numeric(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	max;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_is_digit(str[i]))
		return (0);
	if (sign == -1)
		max = 9223372036854775808ULL;
	else
		max = 9223372036854775807ULL;
	return (ft_is_num_core(str, i, max));
}
