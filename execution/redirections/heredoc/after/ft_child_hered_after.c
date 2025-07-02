/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_hered_after.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:57:34 by akahir            #+#    #+#             */
/*   Updated: 2025/07/02 17:57:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../execution.h"

void ft_child_hered_aft(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
    char **cmd_args;
    int *hered_fd = (int *)in.status;
    int flag_redir;
    char *command;

    command = ft_check_built_redir(curr);
    flag_redir = ft_flag_redir(curr);
    if (in.i == 0 && hered_fd[0] != -1)
    {
        if (dup2(hered_fd[0], 0) == -1)
            (perror("dup2 heredoc"), exit(1));
        close(hered_fd[0]);
    }
    else if (in.i > 0)
    {
        if (dup2(in.pipes[in.i - 1][0], 0) == -1)
            (perror("dup2 pipe input"), exit(1));
    }
    if (in.i < in.n_cmds - 1)
    {
        if (dup2(in.pipes[in.i][1], 1) == -1)
            (perror("dup2 pipe output"), exit(1));
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
        (ft_is_builtins(curr, line_env, in), exit(0));
    if (!curr->cmd || !curr->cmd[0])
        exit(0);
    cmd_args = ft_get_path(curr->cmd[0], env_here.env);
    if (!cmd_args)
	{
		if (curr->cmd[0] && curr->cmd[0][0] >= '0' && curr->cmd[0][0] <= '9')
			(printf("%s: command not found\n", curr->cmd[0]), exit(127));
		else
			(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(127));
	}
    if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
        (perror("execve failed"), exit(1));
}
