/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:15:05 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/06 15:18:24 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wrap_assignment_value(char *s, int val_start)
{
	char	*prefix;
	char	*value;
	char	*tmp;

	prefix = ft_substr(s, 0, val_start);
	value = ft_strjoin_par(ft_strdup("\"", 0, 0), s + val_start);
	tmp = ft_strjoin_par(prefix, value);
	value = ft_strjoin_par(tmp, "\"");
	return (value);
}

int	lookfor_ex(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_space(char *s)
{
	if (semiflag(s) || lookfor_ex(s))
		return (1);
	return (0);
}
