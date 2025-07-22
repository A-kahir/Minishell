/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:02 by akahir            #+#    #+#             */
/*   Updated: 2025/07/22 12:09:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_echo(char **str, t_exec in)
{
	int		i = 1;
	int		flag_n = 0;

	while (str[i] && ft_check(str, &i))
		flag_n = 1;
	while (str[i])
	{
		// if (str[i][0] == '$' && str[i][1] == '\0')
		// 	break ;
		if (ft_strcmp(str[i], "$?") == 0)
		{
			if (in.status)
				write(1, in.status, ft_strlen(in.status));
		}
		else
		{
			int j = 0;
			while (str[i][j])
			{
				if (str[i][j] == '$' && str[i][j + 1] == '?')
				{
					if (in.status)
						write(1, in.status, ft_strlen(in.status));
					j += 2;
				}
				else
				{
					write(1, &str[i][j], 1);
					j++;
				}
			}
		}
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
