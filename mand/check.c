/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:14:04 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/29 15:28:57 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *c)
{
	write(2, "minishell: ", 12);
	write(2, "syntax error near unexpected token `", 37);
	write(2, c, ft_strlen(c));
	write(2, "'\n", 3);
}

static int	is_redirection(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

static int	synt_err2(char **s, int i)
{
	if ((!s[i + 1] || !ft_strcmp(s[i + 1], "|")))
	{
		if (!s[i + 1])
			print_error("newline");
		else
			print_error(s[i + 1]);
		return (0);
	}
	return (1);
}

static int	synt_err(char **s, int i)
{
	if (!ft_strcmp(s[i], "||") && !ft_strcmp(s[i + 1], "|"))
	{
		print_error("|");
		return (0);
	}
	else if (!ft_strcmp(s[i], "|"))
	{
		if (!synt_err2(s, i))
			return (0);
	}
	else if (is_redirection(s[i]))
	{
		if ((!s[i + 1] || is_redirection(s[i + 1])
				|| !ft_strcmp(s[i + 1], "|")))
		{
			if (!s[i + 1])
				print_error("newline");
			else
				print_error(s[i + 1]);
			return (0);
		}
	}
	return (1);
}

int	syntax_error(char **s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (1);
	if ((!ft_strcmp(s[0], "|") || !ft_strcmp(s[0], "||")
			|| !ft_strcmp(s[0], "&&")))
	{
		print_error(s[0]);
		return (0);
	}
	while (s[i])
	{
		if (!synt_err(s, i))
			return (0);
		i++;
	}
	return (1);
}
