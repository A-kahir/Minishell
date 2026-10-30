/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:04:13 by akahir            #+#    #+#             */
/*   Updated: 2025/07/25 19:03:56 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_empty_env(char **env)
{
	int	i;

	if (!env || !env[0])
		return (1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0
			|| ft_strncmp(env[i], "SHLVL=", 6) == 0
			|| ft_strncmp(env[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		return (0);
	}
	return (1);
}
