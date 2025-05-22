/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:25 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 16:29:47 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_env(char **str, char **env)
{
	int	i;
	int j;

	i = 1;
	if (str[i] && strcmp(str[i], "env") == 0)
		i++;
	if (!str[i])
	{
		j = 0;
		while (env[j])
		{
			printf("%s\n", env[j]);
			j++;
		}
		return;
	}
	if (access(str[i], F_OK) != 0)
	{
		printf("env: %s: No such file or directory\n", str[i]);
	}
	else if (access(str[i], X_OK) != 0)
	{
		printf("env: %s: Permission denied\n", str[i]);
	}
}
