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
    if (data->redir->target)
    {
        if (data->redir->target[0] == '$' && data->redir->target[1] != '\0')
            return (printf("minishell: %s: ambiguous redirect\n", data->redir->target), -1);
    }
    inf_fd = open(data->redir->target, O_RDONLY);
    if (inf_fd < 0)
    {
        printf("Minishell: %s: No such file or directory\n", data->redir->target);
        return (-1);
    }
    return (inf_fd);
}
void ft_child_read_f(t_data *curr, t_built *line_env, t_ex_othr env_here, t_exec in)
{
    char **cmd_args;
    char *command;
    int fd;

    fd = ft_open_infile(curr);
    if (fd == -1)
        exit(1);
    if (fd != -1)
    {
        if (dup2(fd, 0) == -1)
            (perror("dup2 input file failed"), exit(1));
        close(fd);
    }
    else if (in.i > 0)
    {
        if (dup2(in.pipes[in.i - 1][0], 0) == -1)
            (perror("dup2 input pipe failed"), exit(1));
    }
    if (in.i < in.n_cmds - 1)
    {
        if (dup2(in.pipes[in.i][1], 1) == -1)
            (perror("dup2 output pipe failed"), exit(1));
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    command = ft_check_built_cmd(curr);
    if (ft_strcmp(command, "built") == 0)
    {
        ft_is_builtins(curr, line_env, in);
        exit(0);
    }
    cmd_args = ft_get_path(curr->cmd[0], env_here.env, line_env);
    if (!cmd_args)
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
	if (execve(cmd_args[0], curr->cmd, env_here.env) == -1)
		(perror("execve failed"), ft_free_split(cmd_args), exit(1));
}

int ft_read_f(t_data *data, t_built *line_env, t_ex_othr env_here)
{
    t_data *curr;
    t_exec in;
    int status;

    in.n_cmds = ft_count_cmds(data);
    if (in.n_cmds == 0)
        return (0);
    in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
    if (!in.pipes)
        return (perror("malloc failed"), 1);
    in.i = 0;
    while (in.i < in.n_cmds - 1)
    {
        if (pipe(in.pipes[in.i]) == -1)
        {
            ft_close_pipes(in.pipes, in.n_cmds);
            free(in.pipes);
            return (perror("Pipe creation failed"), 1);
        }
        in.i++;
    }
    curr = data;
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            ft_close_pipes(in.pipes, in.n_cmds);
            free(in.pipes);
            perror("Fork failed");
        }
        else if (pid == 0)
            ft_child_read_f(curr, line_env, env_here, in);
        curr = curr->next;
        in.i++;
    }
    ft_close_pipes(in.pipes, in.n_cmds);
    while (wait(&status) > 0);
    status = status / 256;
    free(in.pipes);
    return (status);
}
