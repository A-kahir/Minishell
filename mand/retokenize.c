/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:52 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/23 16:23:41 by yael-oua         ###   ########.fr       */
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

static int stayalone(char *s)
{
    int i = 0;
    if (!s || !*s)
        return 0;
    while(s[i] && ft_isalnum(s[i]))
        i++;
    while (s[i])
    {
        if(s[i] && s[i] == '=')
        {
            while (s[i] && s[i] == '=')
            {
                i++;
            }
            if(s[i] == '$')
                return (0);
            else
                break;
        }
        i++;
    }
    return (1);
}

t_data *retokenize(t_data *data, t_built *env, t_exec *in)
{
	t_data *curr = data;
	char **new_data = NULL;
	int i;
    char *quoted;

	while (curr)
	{
		new_data = NULL;
		i = 0;
		while (curr->cmd[i])
        {
            char *token;
            if (semiflag(curr->cmd[i]) || !stayalone(curr->cmd[i]))
            {
                token = extract_retoken(curr->cmd[i], 0, env, in);
                if(semiflag(token))
                {
                    quoted = extract_quoates(token, 0);
                    free(token);
                }
                else
                    quoted = token;
                char *arr[] = {quoted, NULL};
                new_data = ft_strjoinarray(new_data, arr);
                free(quoted);
            }
            else
            {
                token = expanding(curr->cmd[i], env, in);
                char **split = ft_split_par(token, ' ');
                new_data = ft_strjoinarray(new_data, split);
                free(token);
                freedp(split);
            }
            i++;
        }
		freedp(curr->cmd);
		curr->cmd = new_data;
        if (curr->cmd && curr->cmd[0])
		    curr->builtin_type = get_b(curr->cmd[0]);
		curr = curr->next;
	}
	return data;
}