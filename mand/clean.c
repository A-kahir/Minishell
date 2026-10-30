/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:53:01 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/30 11:54:48 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freedp(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		i++;
	}
}

char	*ft_subpar(char *s, int start, int len)
{
	char	*result;
	int		l1;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", 0, 0));
	if (start + len > ft_strlen(s))
		l1 = ft_strlen(s) - start;
	else
		l1 = len;
	if (l1 == 0)
		return (ft_strdup("", 0, 0));
	result = (char *)malloc_cl(sizeof(char) * (l1 + 1), ALLOCATE, 0);
	if (!result)
		return (NULL);
	i = 0;
	while (i < l1 && i < ft_strlen(s))
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	rl_catch_signals = 0;
}
