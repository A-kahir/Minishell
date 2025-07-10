/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:25:08 by akahir            #+#    #+#             */
/*   Updated: 2025/07/10 16:25:17 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char *ft_expand_dollar(char *line, char *status)
{
    int     i = 0;
    int     j = 0;
    char    *result;

    result = malloc(ft_strlen(line) + 20);
    if (!result)
        return (NULL);
    while (line[i])
    {
        if (line[i] == '$' && line[i + 1] == '?')
        {
            int k = 0;
            while (status[k])
                result[j++] = status[k++];
            i += 2;
        }
        else
            result[j++] = line[i++];
    }
    result[j] = '\0';
    return (result);
}
