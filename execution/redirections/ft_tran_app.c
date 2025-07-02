/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tran_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 19:48:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int ft_open_outfile(t_data *data)
{
    int outf_fd;

    outf_fd = -1;
    if (data->redir->target && data->redir->type == 0)
    {
        outf_fd = open(data->redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (outf_fd < 0)
            (perror("Error opening output file"), exit(1));
    }
    else if (data->redir->target && data->redir->type == 1)
    {
        outf_fd = open(data->redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (outf_fd < 0)
            (perror("Error opening output file"), exit(1));
    }
    return (outf_fd);
}

static void ft_child_redir(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
    int fd;
    char **cmds;

    if (in.n_cmds > 1)
    {
        if (in.i > 0)
        {
            if (dup2(in.pipes[in.i - 1][0], 0) == -1)
                (perror("dup2 input failed"), exit(1));
        }
        if (in.i < in.n_cmds - 1)
        {
            if (dup2(in.pipes[in.i][1], 1) == -1)
                (perror("dup2 pipe output failed"), exit(1));
        }
        ft_close_pipes(in.pipes, in.n_cmds);
    }
    if (curr->redir && curr->redir->target)
    {
        fd = ft_open_outfile(curr);
        if (fd == -1)
            (perror("open outfile failed"), exit(1));
        if (dup2(fd, 1) == -1)
            (perror("dup2 outfile failed"), close(fd), exit(1));
        close(fd);
    }
    if (ft_strcmp(ft_check_built_redir(curr), "built") == 0)
    {
        ft_is_builtins(curr, line_env, in);
        exit(0);
    }
    cmds = ft_get_path(curr->cmd[0], env_here.env);
    if (!cmds)
    {
        if (curr->cmd[0] && curr->cmd[0][0] >= '0' && curr->cmd[0][0] <= '9')
            (printf("%s: command not found\n", curr->cmd[0]), exit(127));
        else
            (printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
    }
    if (execve(cmds[0], curr->cmd, env_here.env) == -1)
        (perror("execve failed"), exit(1));
}

void ft_tran_app(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    char **cmds;
    int fd;
    t_exec in;
    t_data *curr;
    pid_t pid;

    curr = data;
    in.n_cmds = ft_count_cmds(data);
    if (in.n_cmds == 1)
    {
        if (curr->cmd == NULL)
        {
            if (curr->redir && curr->redir->target)
            {
                fd = ft_open_outfile(curr);
                write(fd, "", 0);
                close(fd);
            }
            return;
        }
        if (ft_strcmp(curr->cmd[0], "echo") == 0 && curr->redir && curr->redir->target)
        {
            fd = ft_open_outfile(curr);
            int i = 1;
            while (curr->cmd[i] != NULL)
            {
                int j = 0;
                while (curr->cmd[i][j] != '\0')
                {
                    write(fd, &curr->cmd[i][j], 1);
                    j++;
                }
                if (curr->cmd[i + 1] != NULL)
                    write(fd, " ", 1);
                i++;
            }
            write(fd, "\n", 1);
            close(fd);
            return;
        }
        pid = fork();
        if (pid == -1)
            (perror("fork failed"), exit(1));
        if (pid == 0)
            ft_child_redir(curr, line_env, env_here, in);
        wait(NULL);
        return;
    }
    in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
    if (!in.pipes)
        (perror("malloc"), exit(1));
    in.i = 0;
    while (in.i < in.n_cmds - 1)
    {
        if (pipe(in.pipes[in.i]) == -1)
            (perror("pipe creation failed"), free(in.pipes), exit(1));
        in.i++;
    }
    t_data *tmp = data;
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        pid = fork();
        if (pid == -1)
        {
            ft_close_pipes(in.pipes, in.n_cmds - 1);
            (perror("fork failed"), free(in.pipes), exit(1));
        }
        if (pid == 0)
            ft_child_redir(tmp, line_env, env_here, in);
        tmp = tmp->next;
        in.i++;
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    free(in.pipes);
    while (wait(NULL) > 0);
}
