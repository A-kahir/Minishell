/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:39:36 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 16:06:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_len_struct(t_built *line_env)
{
	t_built	*curr;
	int		count;

	curr = line_env;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

static char	*ft_build_env(t_built *curr)
{
	char	*temp;
	char	*env_str;

	temp = ft_strjoin(curr->var, "=");
	if (!temp)
		return (NULL);
	env_str = ft_strjoin(temp, curr->value);
	free(temp);
	if (!env_str)
		return (NULL);
	return (env_str);
}

char	**ft_fill_envp(t_built *line_env)
{
	t_built	*curr;
	char	**envp;
	int		i;
	int		len;

	len = ft_len_struct(line_env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);

	i = 0;
	curr = line_env;
	while (curr)
	{
		if (curr->value)
		{
			envp[i] = ft_build_env(curr);
			if (!envp[i])
			{
				while (--i >= 0)
					free(envp[i]);
				free(envp);
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	envp[i] = NULL;
	return (envp);
}
