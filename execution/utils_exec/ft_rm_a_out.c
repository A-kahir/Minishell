/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_a_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:29:08 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 13:29:31 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_rm_a_out(t_built *line)
{
    t_built *curr;
    
    curr = line;
    while (curr)
    {
        if (ft_strcmp(curr->value, "./a.out") == 0)
        {
            ft_rm_list(&line, curr);
        }
        curr = curr->next;
    }
    return (line);
}
