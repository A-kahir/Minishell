/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:28:26 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 21:41:13 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_cd(char **str)
{
	char *home;

	if (str[1] && str[2])
	{
		printf("minishell: cd: too many arguments\n");
		return;
	}
	if (ft_strcmp(str[0], "cd") == 0 && !str[1])
	{
		home = getenv("HOME");
		if (!home || chdir(home) != 0)
			perror("cd");
	}
	else if (ft_strcmp(str[0], "cd") == 0 && chdir(str[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", str[1]);
		return ;
	}
}
