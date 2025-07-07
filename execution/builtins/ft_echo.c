/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:02 by akahir            #+#    #+#             */
/*   Updated: 2025/07/07 11:58:16 by akahir           ###   ########.fr       */
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

void	ft_echo(char **str, t_exec in)
{
	int		i;
	int		flag_n;

	i = 1;
	flag_n = 0;
	while (str[i] && ft_check(str, &i))
		flag_n = 1;
	while (str[i])
	{
		if (ft_strcmp(str[i], "$?") == 0 && in.status)
		{
			if (in.status)
			{
				int len;
				len = ft_strlen(in.status);
				write(1, in.status, len);
			}
		}
		else if (str[i][0] != '$')
			write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
