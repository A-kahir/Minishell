/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:52 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/17 12:30:39 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int stayalone(char *s)
{
    int i = 0;
    int j = 0;
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

t_data *retokenize(t_data *data, t_built *env)
{
	t_data *curr = data;
	char **new_data = NULL;
	int i;
    char *quoted;
    char    **t;

	while (curr)
	{
		new_data = NULL;
		i = 0;
		while (curr->cmd[i])
        {
            char *token;
            if (semiflag(curr->cmd[i]) || !stayalone(curr->cmd[i]))
            {
                token = extract_retoken(curr->cmd[i], 0, env);
                if(semiflag(token))
                    quoted = extract_quoates(token, 0);
                else
                    quoted = ft_strdup(token);
                char *arr[] = {quoted, NULL};
                t = ft_strjoinarray(new_data, arr);
                freedp(new_data);
                new_data = t;
                free(token);
                free(quoted);
            }
            else
            {
                token = expanding(curr->cmd[i], env);
                char **split = ft_split_par(token, ' ');
                t = ft_strjoinarray(new_data, split);
                freedp(new_data);
                new_data = t;
                free(token);
                freedp(split);
            }
            i++;
        }
		freedp(curr->cmd);
		curr->cmd = new_data;
		curr = curr->next;
	}
	return data;
}
