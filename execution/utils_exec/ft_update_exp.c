/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:15:01 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 17:47:51 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_update_exp(t_built *line, int flag_cd)
{
	t_built *curr;
	int have_old_pwd = 0;
	static int flag;

	curr = line;
	while (curr)
	{
		if (ft_strcmp(curr->var, "OLDPWD") == 0)
		{
			have_old_pwd = 1;
			if (flag == 1)
				line->old_pwd = NULL;
			if (flag_cd == 1 && line->old_pwd)
			{
				free(curr->value);
				curr->value = ft_strdup(line->old_pwd);
			}
			break;
		}
		curr = curr->next;
	}
	flag = 1;
	if (!have_old_pwd)
	{
		if (flag_cd == 1 && line->old_pwd)
			line = ft_add_front(line, "OLDPWD", ft_strdup(line->old_pwd));
		else
			line = ft_add_front(line, "OLDPWD", NULL);
	}
	if (flag_cd == 1)
	{
		curr = line;
		while (curr)
		{
			if (ft_strcmp(curr->var, "PWD") == 0)
			{
				char *buff = getcwd(NULL, 0);
				if (buff)
				{
					free(curr->value);
					curr->value = ft_strdup(buff);
					free(buff);
				}
				break;
			}
			curr = curr->next;
		}
	}
	return (line);
}
