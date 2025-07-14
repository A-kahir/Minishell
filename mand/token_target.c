/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_target.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/13 17:51:13 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_target(char *str, int i, t_built *env)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_start = i;
			cha = str[i++];
			while (str[i] && str[i] != cha)
				i++;
			if (str[i] == cha)
				i++;
			quote_len = i - quote_start;
            if(cha == '\"')
				in = expanding_target(ft_substr_par(str, quote_start, quote_len), env);
			else
				in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
		else
		{
			quote_start = i;
			while (str[i] && (str[i] != ' ' || str[i] == '\t') && str[i] != '\"'
				&& str[i] != '\'')
				i++;
			quote_len = i - quote_start;
			in = expanding_target(ft_substr_par(str, quote_start, quote_len), env);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return (token);
}

char	*extract_retoken(char *str, int i, t_built *env)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_start = i;
			cha = str[i++];
			while (str[i] && str[i] != cha)
				i++;
			if (str[i] == cha)
				i++;
			quote_len = i - quote_start;
            if(cha == '\"')
				in = expanding(ft_substr_par(str, quote_start, quote_len), env);
			else
				in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
		else
		{
			quote_start = i;
			while (str[i] && (str[i] != ' ' || str[i] == '\t') && str[i] != '\"'
				&& str[i] != '\'')
				i++;
			quote_len = i - quote_start;
			in = expanding(ft_substr_par(str, quote_start, quote_len), env);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return (token);
}

int	semiflag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if(s[i] == '\"' || s[i] == '\'')
			return(1);
		i++;
	}
	return(0);
}

// char **last_fix(char **s)
// {
// 	int	i;
// 	char	**t;

// 	i = 0;
// 	t = malloc(sizeof(char *) * (token_len(s) + 1));
// 	while (s[i])
// 	{
// 		if(semiflag(s[i]))
// 			t[i] = extract_quoates(s[i], 0);
// 		else
// 			t[i]= ft_strdup(s[i]);
// 		i++;
// 	}
// 	t[i] =  NULL;
// 	return(t);
// }
