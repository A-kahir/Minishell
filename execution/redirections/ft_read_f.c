/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:48 by akahir            #+#    #+#             */
/*   Updated: 2025/06/27 17:27:49 by akahir           ###   ########.fr       */
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

void ft_child_read_f(t_data *data, t_exec in, char **env, int fd)
{
    char **cmd_args;

    if (fd != -1 && dup2(fd, 0) == -1)
        (perror("dup2 input file failed"), exit(1));
    if (fd != -1)
        close(fd);
    if (fd == -1 && in.i > 0 && dup2(in.pipes[in.i - 1][0], 0) == -1)
        (perror("dup2 input pipe failed"), exit(1));
    if (in.i < in.n_cmds - 1 && dup2(in.pipes[in.i][1], 1) == -1)
        (perror("dup2 output pipe failed"), exit(1));
    ft_close_pipes(in.pipes, in.n_cmds);
    if (!data->cmd || !data->cmd[0])
        exit(0);
    cmd_args = ft_get_path(data->cmd[0], env);
    if (!cmd_args)
        (printf("minishell: %s: command not found\n", data->cmd[0]), exit(1));
    if (execve(cmd_args[0], data->cmd, env) == -1)
        (perror("execve failed"), exit(1));
}

int ft_read_f(t_data *data, t_built *line_env, t_ex_othr env_here)
{
    t_data *curr;
    t_exec in;
    int fd;
    int status;

    status = 0;
    if (data->builtin_type == 0)
    {
        fd = ft_open_infile(data);
        if (fd == -1)
            return (1);
        int i = 1;
        while (data->cmd[i] != NULL)
        {
            int j = 0;
            if (data->cmd[i][j] != '\0')
            {
                while (data->cmd[i][j] != '\0')
                {
                    write(1, &data->cmd[i][j], 1);
                    j++;
                }
                write(1, " ", 1);
            }
            i++;
        }
        close(fd);
        write(1, "\n", 1);
        return (0);
    }
    else
    {
        in.n_cmds = ft_count_cmds(data);
        in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
        if (!in.pipes)
            (perror("malloc failed"), exit(1));
        in.i = 0;
        curr = data;
        while (in.i < in.n_cmds - 1)
        {
            if (pipe(in.pipes[in.i++]) == -1)
                (perror("Pipe creation failed"), exit(1));
        }
        in.i = 0;
        while (in.i < in.n_cmds)
        {
            fd = ft_open_infile(curr);
            if (fd == -1)
            {
                free(in.pipes);
                return (1);
            }
            pid_t pid = fork();
            if (pid == -1)
            {
                ft_close_pipes(in.pipes, in.n_cmds);
                free(in.pipes);
                perror("Fork failed");
                exit(1);
            }
            else if (pid == 0)
                ft_child_read_f(curr, in, env_here.env, fd);
            if (fd != -1)
                close(fd);
            curr = curr->next;
            in.i++;
        }
        ft_close_pipes(in.pipes, in.n_cmds);
        while (wait(&status) > 0);
        status = status / 256;
        free(in.pipes);
    }
    return (status);
}
