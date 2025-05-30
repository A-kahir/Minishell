/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:19:18 by akahir            #+#    #+#             */
/*   Updated: 2025/05/30 20:41:06 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_child_redir(t_data *curr, int pipes[][2], int i, int n_cmds, char **env)
{
	char	**cmd_args;

	if (n_cmds == 1)
    {
        if (dup2(pipes[0][1], 1) == -1)
            (perror("dup2 output failed"), exit(1));
    }
    else
    {
        if (i > 0 && dup2(pipes[i - 1][0], 0) == -1)
            (perror("dup2 input failed"), exit(1));
        if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
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

void ft_case_child(t_data *data, int pp[][2], int i, int n_cmds, char **env)
{
    int fd;
    char **cmd;

    if (i > 0)
    {
        if (dup2(pp[i - 1][0], 0) == -1)
            (perror("dup2 input failed"), exit(1));
    }
    if (i < n_cmds - 1)
    {
        if (dup2(pp[i][1], 1) == -1)
            (perror("dup2 pipe output failed"), exit(1));
    }
    else if (data->redir && data->redir->target)
    {
        fd = ft_open_outfile(data);
        if (fd == -1)
            (perror("open outfile failed"), exit(1));
        if (dup2(fd, STDOUT_FILENO) == -1)
            (perror("dup2 outfile failed"), close(fd), exit(1));
        close(fd);
    }
    ft_close_pipes(pp, n_cmds);
    cmd = ft_get_path(data->cmd[0], env);
    if (!cmd || !cmd[0])
    {
        printf("minishell: %s: command not found\n", data->cmd[0]);
        exit(1);
    }
    if (execve(cmd[0], data->cmd, env) == -1)
        (perror("execve failed"), exit(1));
}


void ft_trancate(t_data *data, t_data *curr, int flag, char **env)
{
    char **cmds;
    int fd;
    int i;
    int j;
    int		pipes[1][2];

    if (flag == 0)
    {
        int n_cmds = ft_count_cmds(data);
        int (*pipes)[2] = malloc(sizeof(int[2]) * (n_cmds - 1));
        if (!pipes)
            (perror("malloc"), exit(1));
        i = 0;
        while (i < n_cmds - 1)
        {
            if (pipe(pipes[i]) == -1)
                (perror("pipe creation failed"), free(pipes), exit(1));
            i++;
        }
        t_data *tmp = data;
        i = 0;
        while (i < n_cmds)
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                ft_close_pipes(pipes, n_cmds - 1);
                (perror("fork failed"), free(pipes), exit(1));
            }
            else if (pid == 0)
            {
                ft_case_child(tmp, pipes, i, n_cmds, env);
                exit(1);
            }
            tmp = tmp->next;
            i++;
        }
        ft_close_pipes(pipes, n_cmds);
        free(pipes);
        while (wait(NULL) > 0);
        return ;
    }
    else
    {
        if (curr->cmd == NULL)
        {
            fd = ft_open_outfile(curr);
            write(fd, "", 0);
            return ;
        }
        else if (ft_strcmp(curr->cmd[0], "echo") == 0 && ft_strcmp(curr->cmd[1], ">") != 0)
        {
            fd = ft_open_outfile(curr);
            i = 1;
            while (curr->cmd[i] != NULL)
            {
                j = 0;
                if (curr->cmd[i][j] != '\0')
                {
                    while (curr->cmd[i][j] != '\0')
                    {
                        write(fd, &curr->cmd[i][j], 1);
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
            cmds = ft_get_path(curr->cmd[0], env);
            if (cmds[0] != NULL)
            {
                pipe(pipes[0]);
                fd = ft_open_outfile(curr);
                pid_t pid = fork();
                if (pid == -1)
                    (close(fd), exit(1));
                else if (pid == 0)
                    ft_child_redir(curr, pipes, 0, 1, env);
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
}
