/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:14:04 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/14 17:58:57 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int	i = 0;
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (quote);
		}
		i++;
	}
	return (0);
}

int	check_before(char *s)
{
	int	i;
	if (!s)
		return (1);
	if(check_unclosed_quotes(s))
	{
		i = check_unclosed_quotes(s);
		write(2, "minishell: unexpected EOF while looking for matching `", 55);
		write(2, &i, 1);
		write(2, "'\n", 3);
		write(2, "minishell: syntax error: unexpected end of file\n", 49);
		return(1);
	}
	return(0);
}

void	print_error(char *c)
{
	t_exec in;
	
	write(2, "minishell: ", 12);
	write(2, "syntax error near unexpected token `", 37);
	write(2, c, ft_strlen(c));
	write(2, "'\n", 3);
}

int	is_redirection(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

int	syntax_error(char **s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if ((!ft_strcmp(s[0], "|") || !ft_strcmp(s[0], "||")))
	{
		print_error(s[0]);
		return (0);
	}
	while (s[i])
	{
		if (!ft_strcmp(s[i], "||"))
		{
			print_error("||");
			return (0);
		}
		if (!ft_strcmp(s[i], "|"))
		{
			if ((!s[i + 1] || !ft_strcmp(s[i + 1], "|")))
			{
				if (!s[i + 1])
					print_error("newline");
				else
					print_error(s[i + 1]);
				return (0);
			}
		}
		if (is_redirection(s[i]))
		{
			if ((!s[i + 1] || is_redirection(s[i + 1]) || !ft_strcmp(s[i + 1], "|")))
			{
				if (!s[i + 1])
					print_error("newline");
				else
					print_error(s[i + 1]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

