/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/05/28 19:25:16 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_child_redir(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char	**cmd_args;

	if (n_cmds == 1)
    {
        if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
            (perror("dup2 output failed"), exit(1));
    }
    else
    {
        if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
            (perror("dup2 input failed"), exit(1));
        if (i < n_cmds - 1 && dup2(pipes[i][1], STDOUT_FILENO) == -1)
            (perror("dup2 output failed"), exit(1));
    }
	ft_close_pipes(pipes, n_cmds);
	cmd_args = ft_get_path(curr->cmd[0], env);
	if (execve(cmd_args[0], curr->cmd, env))
		(perror("execve failed"), exit(1));
	if (!cmd_args[0])
	{
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(1));
	}
}

static int ft_open_outfile(t_data *data)
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
    int		pipes[1][2];

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
        if (!cmds)
        {
            free(cmds);
            return ;
        }
        else if (cmds[0] != NULL)
        {
            pipe(pipes[0]);
            fd = ft_open_outfile(data);
            pid_t pid = fork();
            if (pid == -1)
		        (close(fd), exit(1));
	        else if (pid == 0)
                 ft_child_redir(data, pipes, 0, 1, env);
            else
            {
                close(pipes[0][1]);
                char c;
                while (read(pipes[0][0], &c, 1) > 0)
                {
                    write(fd, &c, 1);
                }
                close(pipes[0][0]);
		        wait(NULL);
                close(fd);
            }
        }
    }
}
