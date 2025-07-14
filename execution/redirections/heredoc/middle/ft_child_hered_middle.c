/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_middle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:09:12 by akahir            #+#    #+#             */
/*   Updated: 2025/07/14 15:53:27 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"


void ft_child_hered_midd(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
    char **cmd_args;
    int *hered_fd;
    char *command;
    char *tmp;
    int i;

    hered_fd = (int *)in.status;
    if (curr == NULL || curr->cmd == NULL || curr->cmd[0] == NULL)
        exit(0);
    if (hered_fd[in.i] != -1)
    {
        if (dup2(hered_fd[in.i], STDIN_FILENO) == -1)
            (perror("dup2 heredoc failed"), exit(1));
        close(hered_fd[in.i]);
    }
    else if (in.i > 0)
    {
        if (dup2(in.pipes[in.i - 1][0], STDIN_FILENO) == -1)
            (perror("dup2 input failed"), exit(1));
    }
    if (in.i < in.n_cmds - 1)
    {
        if (dup2(in.pipes[in.i][1], STDOUT_FILENO) == -1)
            (perror("dup2 output failed"), exit(1));
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    command = ft_check_built_cmd(curr);
    if (command && ft_strcmp(command, "built") == 0)
    {
        ft_is_builtins(curr, line_env, in);
        exit(0);
    }
    if (curr->cmd[0][0] == '$' && ft_check_this_var(curr->cmd[0] + 1, line_env) == 1)
        exit(0);
    cmd_args = ft_get_path(curr->cmd[0], env_here.env, line_env);
    if (!cmd_args || !cmd_args[0])
    {
        write(2, "minishell: ", 12);
        write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
        write(2, ": command not found\n", 21);
        exit(127);
    }
    if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
    {
        perror("execve failed");
        ft_free_split(cmd_args);
        exit(1);
    }
}