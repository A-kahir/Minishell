/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:12:51 by akahir            #+#    #+#             */
/*   Updated: 2025/07/08 15:42:00 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_open_outfile(t_data *data)
{
    int outf_fd;

    if (data->redir->target)
    {
        if (data->redir->target[0] == '$' && data->redir->target[1] != '\0')
            return (printf("minishell: %s: ambiguous redirect\n", data->redir->target), -1);
    }
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
