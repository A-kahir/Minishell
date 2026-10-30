/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:02 by akahir            #+#    #+#             */
/*   Updated: 2025/07/27 15:30:33 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_echo(char **str)
{
	int		i;
	int		flag_n;
	int		j;

	flag_n = 0;
	i = 1;
	while (str[i] && ft_check(str, &i))
		flag_n = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
