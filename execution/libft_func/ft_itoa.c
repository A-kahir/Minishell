/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:38 by akahir            #+#    #+#             */
/*   Updated: 2025/07/01 14:34:39 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	count_len_number(long long n)
{
	int	count;

	count = 1;
	while (n / 10)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	reverse_number(char *stock)
{
	int		start;
	int		end;
	int		i;
	char	temp;

	start = 0;
	end = ft_strlen(stock) - 1;
	i = 0;
	if (stock[i] == '-')
	{
		start++;
		i++;
	}
	while (start < end)
	{
		temp = stock[start];
		stock[start] = stock[end];
		stock[end] = temp;
		start++;
		end--;
	}
}

static void	if_negative(int n, int len_number, char *stock)
{
	int	digit;
	int	i;

	digit = 0;
	i = 0;
	if (n < 0)
	{
		while (len_number > 0)
		{
			if (i == 0)
			{
				stock[i] = '-';
				i++;
			}
			digit = (n % 10) * -1;
			stock[i] = (digit + '0');
			n = n / 10;
			i++;
			len_number--;
		}
	}
	stock[i] = '\0';
}

static void	if_positive(long long n, int len_number, char *stock)
{
	int	digit;
	int	i;

	digit = 0;
	i = 0;
	while (len_number > 0)
	{
		digit = n % 10;
		stock[i] = digit + '0';
		n = n / 10;
		i++;
		len_number--;
	}
	stock[i] = '\0';
}

char	*ft_itoa(int n)
{
	char		*stock;
	int			len_number;

	if (n == 0)
		return (ft_strdup("0"));
	len_number = count_len_number(n);
	if (n < 0)
	{
		stock = (char *)malloc((len_number + 2) * sizeof(char));
	}
	else
	{
		stock = (char *)malloc((len_number + 1) * sizeof(char));
	}
	if (stock == NULL)
		return (NULL);
	if (n < 0)
		if_negative(n, len_number, stock);
	else
		if_positive(n, len_number, stock);
	reverse_number(stock);
	return (stock);
}
