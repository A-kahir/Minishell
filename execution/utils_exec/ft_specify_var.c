/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specify_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:49:36 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 16:26:22 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_specify_var(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (-1);
	if (str[0] >= '0' && str[0] <= '9')
		return (-1);
	if (str[0] == '$')
		return (4);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] != '=')
			return (-1);
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_' || str[i] == '+'))
		{
			return (-1);
		}
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
