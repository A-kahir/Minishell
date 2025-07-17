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

static int    count_size(int n)
{
    int    i;

    i = 0;
    if (n <= 0)
        i = 1;
    while (n != 0)
    {
        n /= 10;
        i++;
    }
    return (i);
}

char    *ft_itoa(int num)
{
    char    *dst;
    int        count;
    long    n;

    n = num;
    count = count_size(n);
    dst = (char *)malloc(sizeof(char) * (count + 1));
    if (!dst)
        return (NULL);
    dst[count] = '\0';
    if (n < 0)
    {
        dst[0] = '-';
        n = -n;
    }
    else if (n == 0)
        dst[0] = '0';
    while (n > 0)
    {
        dst[--count] = (n % 10) + '0';
        n /= 10;
    }
    return (dst);
}
