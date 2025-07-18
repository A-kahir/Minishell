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

void ft_child_read_f(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
    char **cmd_args;
    char *command;
    int fd_result;

    fd_result = ft_fd_redirections(curr->redir);
    if (fd_result == 1)
        exit(1);
    
    if (!curr->cmd || !curr->cmd[0])
        exit(0);
    
    if (in.n_cmds > 1)
    {
        int has_input_redir = 0;
        t_redir *redir = curr->redir;
        while (redir)
        {
            if (redir->type == READ_F)
            {
                has_input_redir = 1;
                break;
            }
            redir = redir->next;
        }
        
        if (!has_input_redir && in.i > 0)
            dup2(in.pipes[in.i - 1][0], STDIN_FILENO);
        
        if (in.i < in.n_cmds - 1)
            dup2(in.pipes[in.i][1], STDOUT_FILENO);
        
        int i = 0;
        while (i < in.n_cmds - 1)
        {
            close(in.pipes[i][0]);
            close(in.pipes[i][1]);
            i++;
        }
    }
    
    command = ft_check_built_cmd(curr);
    if (ft_strcmp(command, "built") == 0)
    {
        ft_is_builtins(curr, line_env, in);
        exit(0);
    }
    
    cmd_args = ft_get_path(curr->cmd[0], env_here.env, line_env);
    if (!cmd_args || !cmd_args[0])
    {
        write(2, "minishell: ", 11);
        write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    
    if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
    {
        if (errno == ENOEXEC)
        {
            char *args[3];
            args[0] = "/bin/sh";
            args[1] = cmd_args[0];
            args[2] = NULL;
            if (execve("/bin/sh", args, env_here.env) == -1)
            {
                perror("execve failed");
                ft_free_split(cmd_args);
                exit(1);
            }
        }
        else
        {
            perror("execve failed");
            ft_free_split(cmd_args);
            exit(1);
        }
    }
}

int ft_read_f(t_data *data, t_built *line_env, t_ex_othr env_here)
{
    t_data *curr;
    t_exec in;
    int status;

    in.n_cmds = ft_count_cmds(data);
    if (in.n_cmds == 0)
        return (0);
    
    if (in.n_cmds > 1)
    {
        in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
        if (!in.pipes)
        {
            perror("malloc failed");
            return (1);
        }
        
        in.i = 0;
        while (in.i < in.n_cmds - 1)
        {
            if (pipe(in.pipes[in.i]) == -1)
            {
                ft_close_pipes(in.pipes, in.i);
                free(in.pipes);
                perror("pipe creation failed");
                return (1);
            }
            in.i++;
        }
    }
    
    curr = data;
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            if (in.n_cmds > 1)
            {
                ft_close_pipes(in.pipes, in.n_cmds - 1);
                free(in.pipes);
            }
            perror("fork failed");
            return (1);
        }
        else if (pid == 0)
            ft_child_read_f(curr, line_env, env_here, in);
        
        curr = curr->next;
        in.i++;
    }
    
    if (in.n_cmds > 1)
    {
        ft_close_pipes(in.pipes, in.n_cmds - 1);
        free(in.pipes);
    }
    
    while (wait(&status) > 0)
        ;
    
    return (WEXITSTATUS(status));
}
