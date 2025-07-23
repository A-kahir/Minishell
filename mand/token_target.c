/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_target.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:38 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/23 15:57:07 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_target(char *str, int i, t_built *env, t_exec *innn)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;
	char	*tmp;

	token = NULL;
	while (str[i] && (str[i] != ' ' || str[i] != '\t'))
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
			{
				tmp = ft_substr_par(str, quote_start, quote_len) ;
				in = expanding_target(tmp, env, innn);
				free(tmp);
			}
			else
				in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
		else
		{
			quote_start = i;
			while (str[i] && (str[i] != ' ' || str[i] != '\t') && str[i] != '\"'
				&& str[i] != '\'')
				i++;
			quote_len = i - quote_start;
			tmp = ft_substr_par(str, quote_start, quote_len) ;
			in = expanding_target(tmp, env, innn);
			token = ft_strjoin_par(token, in);
			free(tmp);
			free(in);
		}
	}
	return (token);
}

char	*extract_retoken(char *str, int i, t_built *env, t_exec *in)
{
	char	*token;
	char	*result;
	int		quote_len;
	int		quote_start;
	char	cha;
	char	*tmp;

	token = NULL;
	while (str[i] && (str[i] != ' ' || str[i] != '\t'))
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
			{
				tmp = ft_substr_par(str, quote_start, quote_len);
				result = expanding(tmp, env, in);
				free(tmp);
			}
			else
				result = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, result);
			free(result);
		}
		else
		{
			quote_start = i;
			while (str[i] && (str[i] != ' ' || str[i] != '\t') && str[i] != '\"'
				&& str[i] != '\'')
				i++;
			quote_len = i - quote_start;
			tmp = ft_substr_par(str, quote_start, quote_len);
			result = expanding(tmp, env, in);
			token = ft_strjoin_par(token, result);
			free(tmp);
			free(result);
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

