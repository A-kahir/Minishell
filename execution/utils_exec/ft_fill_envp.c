/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:39:36 by akahir            #+#    #+#             */
/*   Updated: 2025/06/26 15:40:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_len_struct(t_built *line_env)
{
	t_built *curr;
	int count;

	curr = line_env;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char **ft_fill_envp(t_built *line_env)
{
	t_built *curr;
	char **envp;
	char *temp;
	int i;
	int len;

	len = ft_len_struct(line_env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	curr = line_env;
	i = 0;
	while (curr)
	{
		if (curr->value)
		{
			temp = ft_strjoin(curr->var, "=");
			if (!temp)
			{
				ft_free_split(envp);
				return (NULL);
			}
			envp[i] = ft_strjoin(temp, curr->value);
			free(temp);
			if (!envp[i])
			{
				ft_free_split(envp);
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	envp[i] = NULL;
	return (envp);
}