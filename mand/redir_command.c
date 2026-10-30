/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:32:53 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/03 12:23:30 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_red(char **s, int i, int k)
{
	int	j;

	j = -1;
	while (s[i] && i < k)
	{
		if (check_redirection(s[i]) != NOT_REDIR)
		{
			j = i;
			break ;
		}
		i++;
	}
	return (j);
}

t_redir	*creatn2(t_norm *norm, t_built *env, t_exec *in)
{
	int		j;
	t_redir	*redir_node;
	t_redir	*last_redir;
	t_redir	*new_redir;

	redir_node = NULL;
	last_redir = NULL;
	j = check_red(norm->s, norm->k, norm->i);
	while (j >= 0)
	{
		new_redir = create_redir_node(check_redirection(norm->s[j]),
				norm->s[j + 1], env, in);
		if (!redir_node)
			redir_node = new_redir;
		else
			last_redir->next = new_redir;
		last_redir = new_redir;
		j = check_red(norm->s, j + 2, norm->i);
	}
	return (redir_node);
}

int	command2(char **s, int j, int k)
{
	int	count;

	count = 0;
	while (j < k && s[j])
	{
		if (check_redirection(s[j]) == NOT_REDIR)
			count++;
		else
			j += 1;
		j++;
	}
	return (count);
}

char	**command(char **s, int i, int k)
{
	int		j;
	int		count;
	char	**tmp;
	int		idx;

	1 && (j = i, idx = 0, count = command2(s, i, k));
	tmp = malloc_cl(sizeof(char *) * (count + 1), ALLOCATE, 0);
	if (!tmp)
		return (NULL);
	while (j < k && s[j])
	{
		if (check_redirection(s[j]) == NOT_REDIR)
		{
			tmp[idx++] = ft_strdup(s[j], 0, 0);
		}
		else
		{
			j++;
			if (j <= k && s[j])
				j++;
			continue ;
		}
		j++;
	}
	return (tmp[idx] = NULL, tmp);
}
