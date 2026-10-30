/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:49:44 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/27 13:35:48 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize(char *str)
{
	int		count;
	char	**tokens;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	count = count_tokens(str);
	tokens = malloc_cl(sizeof(char *) * (count + 1), ALLOCATE, 0);
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		tokens[j++] = get_token(str, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
