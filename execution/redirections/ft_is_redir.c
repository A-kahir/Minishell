/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/05/31 14:06:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, char **env)
{
    t_data *curr;
    
    curr = data;
    int flag = 0;
    while (curr)
    {
        if (curr->redir && curr->redir->type != -1)
        {
            if (curr == data)
                flag = 1;
            break;
        }
        curr = curr->next;
    }
    if (curr->redir->type == 0 || curr->redir->type == 1)
    {
        ft_trancate(data, curr, flag, env);
    }
    // else if (curr->redir->type == 1)
    // {
    //     printf("append\n");
    // }
    else if (curr->redir->type == 2)
    {
        printf("Read_F\n");
    }
    else if (curr->redir->type == 3)
    {
        printf("Herdoc\n");
    }
}
