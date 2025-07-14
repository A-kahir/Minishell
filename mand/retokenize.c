/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:52 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/13 16:42:10 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *retokenize(t_data *data, t_built *env)
{
	t_data *curr = data;
	char **new_data = NULL;
	int i;

	while (curr)
	{
		new_data = NULL;
		i = 0;
		while (curr->cmd[i])
        {
            char *token;
            if (semiflag(curr->cmd[i]))
            {
                token = extract_retoken(curr->cmd[i], 0, env);
                char *quoted = extract_quoates(token, 0);
                char *arr[] = {quoted, NULL};
                new_data = ft_strjoinarray(new_data, arr);
                free(token);
                free(quoted);
            }
            else
            {
                token = expanding(curr->cmd[i], env);
                char **split = ft_split_par(token, ' ');
                new_data = ft_strjoinarray(new_data, split);
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
