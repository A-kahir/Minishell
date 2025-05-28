/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/05/28 19:22:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_is_redir(t_data *data, char **env)
{
    if (data->redir->type == 0)
    {
        ft_trancate(data, env);
    }
    else if (data->redir->type == 1)
    {
        printf("append\n");
    }
    else if (data->redir->type == 2)
    {
        printf("Read_F\n");
    }
    else if (data->redir->type == 3)
    {
        printf("Herdoc\n");
    }
}
