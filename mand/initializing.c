/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:42 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/14 14:36:05 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_type_buil	get_b(char *s)
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


int	find_pipe(char **s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			c++;
		if (!ft_strcmp(s[i], "<<"))
		{
			c = 0;
			return (c);	
		}
		i++;
	}
	return (c);
}
char	*extract_quoates(char *str, int i)
{
	char	*token;
	char	*in;
	int		quote_len;
	int		quote_start;
	char	cha;

	token = NULL;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			cha = str[i];
			i++;
			quote_start = i;
			while (str[i] && str[i] != cha)
				i++;
			quote_len = i - quote_start;
			in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
			if (str[i] == cha)
				i++;
		}
		else
		{
			quote_start = i;
			while (str[i] && (str[i] != ' ' || str[i] == '\t') && str[i] != '\"'
				&& str[i] != '\'' && !is_operator(str[i]))
				i++;
			quote_len = i - quote_start;
			in = ft_substr_par(str, quote_start, quote_len);
			token = ft_strjoin_par(token, in);
			free(in);
		}
	}
	return(token);
}

t_redir *create_redir_node(t_type_redir type, char *target, t_built *env)
{
	t_redir *new = malloc(sizeof(t_redir));
	if (!new || !target) 
		return (NULL);
	new->type = type;
	if (type == HEREDOC)
	{
		if(semiflag(target))
			new->target = extract_quoates(target, 1);
		else
			new->target = ft_strdup(target);
	}
	else if (semiflag(target))
		new->target = extract_quoates(extract_target(target, 0, env), 0);
	else
		new->target = extract_target(target, 0, env);
	if (!new->target) 
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}



t_type_redir check_redirection(char *token)
{
	if (!token || !*token) 
		return (NOT_REDIR);
	if (!ft_strcmp(token, ">")) 
		return (TRUNCATE);
	if (!ft_strcmp(token, ">>")) 
		return (APPEND);
	if (!ft_strcmp(token, "<")) 
		return (READ_F);
	if (!ft_strcmp(token, "<<")) 
		return (HEREDOC);
	return (NOT_REDIR);
}

int	check_red(char **s, int i, int k)
{
	int	j;

	j = -1;
	while (s[i] && i < k)
	{
		if (check_redirection(s[i]) != NOT_REDIR)
		{
			j = i;
			break;
		}
		i++;
	}
	return (j);
}


t_data *create_data_node(t_type_node t)
{
	t_data *node = malloc(sizeof(t_data));
	if (!node) return (NULL);
	node->type = t;
	node->redir = NULL;
	node->builtin_type = NOT_BUILTIN;
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}
t_redir	*creatn2(char **s, int i, int k, t_built *env)
{
	int	j;
	t_redir *redir_node = NULL;
	t_redir *last_redir = NULL;

	j = check_red(s, i, k);
	while (j >= 0)
	{
		t_redir *new_redir = create_redir_node(check_redirection(s[j]), s[j + 1], env);
		if (!redir_node)
			redir_node = new_redir;
		else
			last_redir->next = new_redir;
		last_redir = new_redir;
		j = check_red(s, j + 2, k);
	}
	return(redir_node);
}

char	**command(char **s, int i, int k)
{
	int	j;
	int count;
	char	**tmp;
	int idx;

	count = 0;
	j = i;
	while (j < k && s[j])
	{
		if (check_redirection(s[j]) == NOT_REDIR)
			count++;
		else
			j += 1;
		j++;
	}

	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (NULL);

	j = i;
	idx = 0;
	while (j < k && s[j])
	{
		if (check_redirection(s[j]) == NOT_REDIR)
		{
			tmp[idx++] = ft_strdup(s[j]);
		}
		else
		{
			j++;
			if (j <= k && s[j])
				j++;
			continue;
		}
		j++;
	}
	tmp[idx] = NULL;
	return (tmp);
}

t_data	*creatn(char **s, int i, int k, t_type_node t, t_built *env)
{
	t_data	*cmd;
	int	j = 0;

	cmd = create_data_node(t);
	if (!cmd)
		return (n_clean(cmd), NULL);
	cmd->type = t;
	j = check_red(s, i, k);
	if (j >= 0)
	{
		cmd->redir= creatn2(s, i, k, env);
		cmd->cmd= command(s, i, k);
	}
	else
	{
		cmd->cmd = ft_subarray(s, i, k);
		cmd->redir = NULL;
	}
	if (cmd->cmd && cmd->cmd[0])
		cmd->builtin_type = get_b(cmd->cmd[0]);
	return (cmd);
}

t_data	*loop(char **s, t_data *cmd, t_type_node t, t_built *env)
{
	int		i = 0;
	int		k = 0;
	t_data	*curr = NULL;
	t_data	*node = NULL;

	while (s[i])
	{
		if (!ft_strcmp(s[i], "|") || !ft_strcmp(s[i], "||") || !ft_strcmp(s[i], "&&"))
		{
			curr = creatn(s, k, i, t, env);
			if (!cmd)
				cmd = curr;
			else
				node->next = curr;
			node = curr;
			k = i + 1;
		}
		i++;
	}
	if (k < i)
	{
		curr = creatn(s, k, i, t, env);
		if (!cmd)
			cmd = curr;
		else
			node->next = curr;
	}
	return (cmd);
}

t_data	*part2(char **s, t_built *env)
{
	t_data	*cmd;

	cmd = NULL;
	cmd = loop(s, cmd, CMD_NODE, env);
	return (cmd);
}

t_data	*part1(char **s, t_built *env)
{
	t_data *cmd;

	cmd = NULL;
	if(!find_pipe(s))
		return (part2(s, env));
	else
	{
		cmd = loop(s, cmd, PIPE_NODE, env);
	}
	return (cmd);
}
