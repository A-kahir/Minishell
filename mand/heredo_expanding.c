/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredo_expanding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:20:46 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/07 10:26:09 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*helper_func2(char *var, char *result, t_exec *in)
{
	char	*tmp2;

	if (!ft_strcmp(var, "?"))
	{
		tmp2 = ft_strjoin_par(result, in->status);
		result = tmp2;
	}
	else if (!ft_strcmp(var, ""))
	{
		tmp2 = ft_strjoin_par(result, "$");
		result = tmp2;
	}
	else if (!ft_strcmp(var, "_"))
	{
		tmp2 = ft_strjoin_par(result, in->last_cmd);
		result = tmp2;
	}
	return (result);
}

static char	*helper_func(char *result, t_expanding *l, t_built *env, t_exec *in)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*val;
	char	*tmp2;

	tmp = ft_subpar(l->s, l->start, l->i - l->start);
	i = l->i + 1;
	while (l->s[i] && (ft_isalnum(l->s[i]) || l->s[i] == '_' || l->s[i] == '?'))
		i++;
	var = ft_subpar(l->s, l->i + 1, i - (l->i + 1));
	val = get_env_value(var, env);
	tmp2 = ft_strjoin_par(result, tmp);
	result = tmp2;
	if (val)
	{
		tmp2 = ft_strjoin_par(result, val);
		result = tmp2;
	}
	else
		result = helper_func2(var, result, in);
	return (result);
}

char	*expanding_heredoc(char *s, t_built *env, t_exec *in)
{
	t_expanding	exp;
	char		*result;

	1 && (exp.i = 0, exp.start = 0, result = NULL, exp.s = s);
	while (exp.s[exp.i])
	{
		if (!ft_strncmp(exp.s + exp.i, "$$", 2))
			1 && (exp.i += 2, exp.start += 2);
		else if (exp.s[exp.i] == '$' && exp.s[exp.i + 1] != '$')
		{
			result = helper_func(result, &exp, env, in);
			exp.i++;
			while (exp.s[exp.i] && (ft_isalnum(exp.s[exp.i])
					|| exp.s[exp.i] == '_' || exp.s[exp.i] == '?'))
				exp.i++;
			exp.start = exp.i;
		}
		else
			exp.i++;
	}
	if (exp.start < exp.i)
		result = ft_strjoin_par(result,
				ft_subpar(exp.s, exp.start, exp.i - exp.start));
	return (result);
}
