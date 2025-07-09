/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:42 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/07 14:54:26 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

char **last_fix(char **s)
{
	int	i;
	char	**t;

	i = 0;
	t = malloc(sizeof(char *) * (token_len(s) + 1));
	while (s[i])
	{
		if(semiflag(s[i]))
			t[i] = ft_strdup(extract_quoates(s[i], 0));
		else
			t[i]= ft_strdup(s[i]);
		i++;
	}
	t[i] =  NULL;
	return(t);
}
t_redir *create_redir_node(t_type_redir type, char *target)
{
	t_redir *new = malloc(sizeof(t_redir));
	if (!new || !target) 
		return (NULL);
	new->type = type;
	new->target = extract_quoates(target, 0);
	if (!new->target) 
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}


int	check_red(char **s, int i, int k)
{
	int	j;

	j = -1;
	while (s[i] && i <= k)
	{
		if(!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], "<") 
			|| !ft_strcmp(s[i], "<<") || !ft_strcmp(s[i], ">>"))
			j = i;
		i++;
	}
	return (j);
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

t_data	*creatn(char **s, int i, int k, t_type_node t)
{
	t_data	*cmd;
	int	j;
	int	quote_len;

	j = 0;
	quote_len = token_len(s);
	cmd = create_data_node(t);
	if (!cmd)
		return(n_clean(cmd), NULL);
	cmd->type = t;
	j = check_red(s, i, k);
	if (j >= 0)
	{
		cmd->redir = create_redir_node(check_redirection(s[j]), s[j + 1]);
		cmd->cmd = ft_strjoinarray(ft_subarray(last_fix(s), i, j), ft_subarray(last_fix(s), j + 2, k));
		printf("->: %s\n", cmd->cmd[0]);
	}
	else
	{
		cmd->cmd = ft_subarray(last_fix(s), i, k);
		cmd->redir = NULL;
	}
	if (cmd->cmd && cmd->cmd[0])
		cmd->builtin_type = get_b(cmd->cmd[0]);
	return (cmd);
}

t_data	*loop(char **s, t_data *cmd, t_type_node t)
{
	int	i;
	int	k;
	t_data *curr;
	t_data *node;
	
	1 && (k = 0, i = 0, curr = NULL, node = NULL);
	while(s[i])
	{
		if (!ft_strcmp(s[i], "|") || !ft_strcmp(s[i], "||") || !ft_strcmp(s[i], "&&"))
		{
			curr = creatn(s, k, (i), t);
			if(!cmd)
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
		curr = creatn(s, k, i, t);
		if (!cmd)
			cmd = curr;
		else
			node->next = curr;
	}
	return (cmd);
}

t_data	*part2(char **s)
{
	t_data	*cmd;

	cmd = NULL;
	cmd = loop(s, cmd, CMD_NODE);
	return (cmd);
}

t_data	*part1(char **s)
{
	t_data *cmd;

	cmd = NULL;
	if(!find_pipe(s))
		return (part2(s));
	else
	{
		cmd = loop(s, cmd, PIPE_NODE);
	}
	return (cmd);
}
