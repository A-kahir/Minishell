/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:30:14 by akahir            #+#    #+#             */
/*   Updated: 2025/06/19 13:30:37 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_sort_vars(t_built *head)
{
    t_built *a;
    t_built *b;

    if (!head || !head->next)
        return (head);
    a = head;
    while (a != NULL)
    {
        b = a->next;
        while (b != NULL)
        {
            if (ft_strcmp(a->var, b->var) > 0)
            {
                char *tmp_var = a->var;
                char *tmp_value = a->value;
                a->var = b->var;
                a->value = b->value;
                b->var = tmp_var;
                b->value = tmp_value;
            }
            b = b->next;
        }
        a = a->next;
    }
    return (head);
}
