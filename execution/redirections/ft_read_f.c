/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:48 by akahir            #+#    #+#             */
/*   Updated: 2025/06/25 13:04:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_open_infile(t_data *data)
{
    int inf_fd;

    if (!data->redir || !data->redir->target)
        return (-1);
    inf_fd = open(data->redir->target, O_RDONLY);
    if (inf_fd < 0)
    {
        printf("Minishell: %s: No such file or directory\n", data->redir->target);
        return (-1);
    }
    return (inf_fd);
}

void ft_child_read_f(t_data *data, int pipes[][2], int i, int n_cmds, int fd, char **env)
{
    char **cmd_args;

    if (fd != -1 && dup2(fd, 0) == -1)
        (perror("dup2 input file failed"), exit(1));
    if (fd != -1)
        close(fd);
    if (fd == -1 && i > 0 && dup2(pipes[i - 1][0], 0) == -1)
        (perror("dup2 input pipe failed"), exit(1));
    if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
        (perror("dup2 output pipe failed"), exit(1));
    ft_close_pipes(pipes, n_cmds);
    if (!data->cmd || !data->cmd[0])
        exit(0);
    cmd_args = ft_get_path(data->cmd[0], env);
    if (!cmd_args)
        (printf("minishell: %s: \n", data->cmd[0]), exit(1));
    if (execve(cmd_args[0], data->cmd, env) == -1)
        (perror("execve failed"), exit(1));
}

void ft_read_f(t_data *data, t_data *curr, int flag, char **env)
{
    int fd;
    int i;
    int j;

    if (data->cmd == NULL)
        return;
    else if (ft_strcmp(data->cmd[0], "echo") == 0)
    {
        fd = ft_open_infile(data);
        if (fd == -1)
            return;
        i = 1;
        while (curr->cmd[i] != NULL)
        {
            j = 0;
            if (curr->cmd[i][j] != '\0')
            {
                while (curr->cmd[i][j] != '\0')
                {
                    write(1, &curr->cmd[i][j], 1);
                    j++;
                }
                write(1, " ", 1);
            }
            i++;
        }
        close(fd);
        write(1, "\n", 1);
        return ;
    }
    else
    {
        int n_cmds = ft_count_cmds(data);
        int (*pipes)[2] = malloc(sizeof(int[2]) * (n_cmds - 1));
        int i = 0;
        t_data *temp = data;
        while (i < n_cmds - 1)
        {
            if (pipe(pipes[i++]) == -1)
                (perror("Pipe creation failed"), exit(1));
        }
        i = 0;
        while (i < n_cmds)
        {
            int flag_exit = 0;
            int fd = ft_open_infile(temp);
            if (fd == -1)
                return;
            pid_t pid = fork();
            if (pid == -1)
            {
                ft_close_pipes(pipes, n_cmds);
                perror("Fork failed");
                exit(1);
            }
            else if (pid == 0)
                ft_child_read_f(temp, pipes, i, n_cmds, fd, env);
            if (fd != -1)
                close(fd);
            temp = temp->next;
            i++;
        }
        ft_close_pipes(pipes, n_cmds);
        while (wait(NULL) > 0);
        free(pipes);
    }
}
