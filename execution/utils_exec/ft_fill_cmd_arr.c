/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:20:55 by akahir            #+#    #+#             */
/*   Updated: 2025/05/24 15:30:35 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_fill_cmd_arr(t_data *root, t_data **arr, int *idx)
{
    if (!root)
        return;
    if (root->type == CMD_NODE)
    {
        arr[*idx] = root;
        (*idx)++;
    }
    else if (root->type == PIPE_NODE)
    {
        ft_fill_cmd_arr(root->left, arr, idx);
        ft_fill_cmd_arr(root->right, arr, idx);
    }
}
