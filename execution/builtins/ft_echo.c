/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:02 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:48:09 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static	int	ft_check(char **str, int *i)
{
	int	j;

	j = 1;
	if (!str[*i] || str[*i][0] != '-' || str[*i][1] != 'n')
		return (0);
	while (str[*i][j] == 'n')
		j++;
	if (str[*i][j] == '\0')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	if (str[i] && ft_strcmp(str[i], "echo") == 0)
		i++;
	while (str[i] && ft_check(str, &i))
		flag = 1;
	while (str[i] && str[i][0] != '$')
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
	if (!flag)
		write(1, "\n", 1);
}
