/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:52 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/06 16:58:36 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type_buil	get_b(char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		return (IS_ECHO);
	else if (ft_strcmp(s, "cd") == 0)
		return (IS_CD);
	else if (ft_strcmp(s, "pwd") == 0)
		return (IS_PWD);
	else if (ft_strcmp(s, "export") == 0)
		return (IS_EXPORT);
	else if (ft_strcmp(s, "unset") == 0)
		return (IS_UNSET);
	else if (ft_strcmp(s, "env") == 0)
		return (IS_ENV);
	else if (ft_strcmp(s, "exit") == 0)
		return (IS_EXIT);
	else
		return (NOT_BUILTIN);
}

static char	*add_quotes_to_assignments(char *s)
{
	int	i;
	int	eq_pos;
	int	plus_eq;
	int	val_start;

	1 && (i = 0, eq_pos = -1, plus_eq = 0);
	while (s[i])
	{
		if (s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
		{
			eq_pos = i;
			plus_eq = (s[i] == '+');
			break ;
		}
		i++;
	}
	val_start = eq_pos + 1 + plus_eq;
	while (s[val_start] == '=')
		val_start++;
	if (eq_pos == -1 || check_space(ft_subpar(s, 0, i)) == 1)
		return (ft_strdup(s, 0, 0));
	else if (!semiflag(s + val_start))
		return (wrap_assignment_value(s, val_start));
	return (s);
}

static char	**loop(char **s)
{
	int		i;
	int		count;
	char	**t;

	if (!s)
		return (NULL);
	count = 0;
	while (s[count])
		count++;
	t = malloc_cl(sizeof(char *) * (count + 1), 0, 0);
	if (!t)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (semiflag(s[i]))
			t[i] = extract_quoates(s[i], 0);
		else
			t[i] = ft_strdup(s[i], 0, 0);
		i++;
	}
	t[i] = NULL;
	return (t);
}

t_data	*retokenize(t_data *data, t_built *env, t_exec *in)
{
	t_data			*curr;
	char			**new_data;
	char			*retok;

	curr = data;
	while (curr)
	{
		1 && (new_data = NULL, in->i = 0);
		while (curr->cmd && curr->cmd[in->i])
		{
			retok = extract_retoken(add_quotes_to_assignments(
						curr->cmd[in->i]), 0, env, in);
			new_data = ft_joinarray(new_data, ft_split_par(retok, ' '));
			in->i++;
		}
		freedp(curr->cmd);
		curr->cmd = loop(new_data);
		freedp(new_data);
		if (curr->cmd && curr->cmd[0])
			curr->builtin_type = get_b(curr->cmd[0]);
		curr = curr->next;
	}
	return (data);
}
