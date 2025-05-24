/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:31:34 by akahir            #+#    #+#             */
/*   Updated: 2025/05/24 15:30:12 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_count_cmd_nodes(t_data *data)
{
    int total;
    
    if (!data)
        return (0);
    if (data->type == CMD_NODE)
        return (1);
    total += ft_count_cmd_nodes(data->left) + ft_count_cmd_nodes(data->right);
    return (total);
}
