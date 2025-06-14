/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:34 by akahir            #+#    #+#             */
/*   Updated: 2025/06/14 18:37:14 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_handle_middle(t_data *data, char **env)
{
    int n_cmds;
    int i;
    pid_t	pid;
	int		(*pipes)[2];

    printf("data->cmd[0]=> %s\n", data->cmd[0]);
    printf("data->cmd[1]=> %s\n", data->cmd[1]);
    printf("data->next->cmd[0]=> %s\n", data->next->cmd[0]);
    printf("data->next->cmd[1]=> %s\n", data->next->cmd[1]);
    n_cmds = ft_count_cmds(data);
    i = 0;
    pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
    while (i < n_cmds - 1)
    {
        if (pipe(pipes[i++]) == -1)
            (perror("pipe creation failed"), exit(1));
    }
    i = 0;
    while (i < n_cmds)
    {
        pid = fork();
        if (pid == -1)
            (ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
        else if (pid == 0)
            ft_child_hered_midd(data, pipes, i, n_cmds, env);
        data = data->next;
        i++;
    }
    ft_close_pipes(pipes, n_cmds);
    while (wait(NULL) > 0);
	free(pipes);
}
