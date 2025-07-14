/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:58:25 by akahir            #+#    #+#             */
/*   Updated: 2025/07/10 19:26:53 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// int ft_open_infile(t_data *data)
// {
//     int inf_fd;

//     if (!data->redir || !data->redir->target)
//         return (-1);
//     if (data->redir->target)
//     {
//         if (data->redir->target[0] == '$' && data->redir->target[1] != '\0')
//             return (printf("minishell: %s: ambiguous redirect\n", data->redir->target), -1);
//     }
//     inf_fd = open(data->redir->target, O_RDONLY);
//     if (inf_fd < 0 && data->redir->type == 2)
//     {
//         write(2, "minishell: ", 12);
//         write(2, data->redir->target, ft_strlen(data->redir->target));
//         write(2, ": No such file or directory\n", 29);
//         return (-1);
//     }
//     return (inf_fd);
// }
