/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:47:28 by akahir            #+#    #+#             */
/*   Updated: 2025/07/14 17:25:19 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_status(t_exec in, char *value)
{
    if (in.status)
    {
        free(in.status);
        in.status = NULL;
    }
    in.status = ft_strdup(value);
}
