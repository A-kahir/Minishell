/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:13:53 by akahir            #+#    #+#             */
/*   Updated: 2025/07/08 15:26:56 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ft_child_redir(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
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
            exit(1);
        if (dup2(fd, 1) == -1)
            (perror("dup2 outfile failed"), close(fd), exit(1));
        close(fd);
    }
    if (ft_strcmp(ft_check_built_cmd(curr), "built") == 0)
    {
        ft_is_builtins(curr, line_env, in);
        exit(0);
    }
    cmds = ft_get_path(curr->cmd[0], env_here.env, line_env);
    if (!cmds)
	{
		if (curr->cmd[0] && curr->cmd[0][0] >= '0' && curr->cmd[0][0] <= '9')
		{
			write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
			write(2, ": command not found\n", 21);
		}
		else
		{
			write(2, "minishell: ", 11);
			write(2, curr->cmd[0], ft_strlen(curr->cmd[0]));
			write(2, ": command not found\n", 21);
		}
		exit(127);
	}
	if (execve(cmds[0], curr->cmd, env_here.env) == -1)
		(perror("execve failed"), ft_free_split(cmds), exit(1));
}
