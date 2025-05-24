/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/05/24 18:24:32 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_open_outfile(t_data *data)
{
    int outf_fd;

    if (data->redir->target)
    {
        outf_fd = open(data->redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (outf_fd < 0)
        {
            perror("Error opening output file");
            exit(1);
        }
    }
    return (outf_fd);
}

void ft_trancate(t_data *data, char **env)
{
    char **cmds;
    int fd;
    int i;
    int j;

    if (ft_strcmp(data->cmd[0], "echo") == 0 && ft_strcmp(data->cmd[1], ">") != 0)
    {
        fd = ft_open_outfile(data);
        i = 1;
        while (data->cmd[i] != NULL)
        {
            j = 0;
            if (data->cmd[i][j] != '\0')
            {
                while (data->cmd[i][j] != '\0')
                {
                    write(fd, &data->cmd[i][j], 1);
                    j++;
                }
                write(fd, " ", 1);
            }
            i++;
        }
        close(fd);
    }
    else
    {
        cmds = ft_get_path(data->cmd[0], env);
        printf("cmd=>222 %s\n", cmds[0]);
        // printf("Minishell: %d")
    }
}
