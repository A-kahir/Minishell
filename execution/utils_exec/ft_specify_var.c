/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specify_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:49:36 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 23:20:19 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_check_valid_chars(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] != '=')
			return (-1);
		if (str[0] == '+' && str[1] == '=')
			return (-1);
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

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
	return (ft_check_valid_chars(str, i));
}
