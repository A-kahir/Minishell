/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:12:51 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 17:26:06 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_open_outfile(t_data *data)
{
    int outf_fd;

    outf_fd = -1;
    if (data->redir->target && data->redir->type == 0)
    {
        outf_fd = open(data->redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (outf_fd < 0)
            return (perror("Error opening output file"), -1);
    }
    else if (data->redir->target && data->redir->type == 1)
    {
        outf_fd = open(data->redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (outf_fd < 0)
            return (perror("Error opening output file"), -1);
    }
    return (outf_fd);
}
