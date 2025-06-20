/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:50:40 by akahir            #+#    #+#             */
/*   Updated: 2025/06/20 13:02:35 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_built *ft_add_back(t_built *line, char *var, char *value)
{
    t_built *new_node;
    t_built *curr;

    new_node = malloc(sizeof(t_built));
    if (!new_node)
        return (line);
    new_node->var = ft_strdup(var);
    if (value != NULL)
        new_node->value = ft_strdup(value);
    else
        new_node->value = NULL;
    new_node->next = NULL;
    if (!line)
        return (new_node);
    curr = line;
    while (curr->next)
        curr = curr->next;
    curr->next = new_node;
    return (line);
}

