/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:35:04 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 20:48:24 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void ft_child_pro_f(t_data *data, int (*pipes)[2], int i, int n_cmds, char **env, t_built *line_env, t_heredoc *heredoc)
{
    char *command;
	char **cmd_args;

    if (i < n_cmds - 1)
        dup2(pipes[i][1], 1);
    if (i > 0)
        dup2(pipes[i - 1][0], 0);
    ft_close_pipes(pipes, n_cmds);
    command = ft_check_built_redir_f(data, env);
    if (command == NULL)
        command = "cmd";
    if (ft_flag_redir(data) == 1)
        ft_is_redir(data, env, heredoc);
    if (ft_strcmp(command, "built") == 0 && data->builtin_type != -1)
    {
        ft_is_builtins_f(data, line_env, env);
        exit(0);
    }
	cmd_args = ft_get_path(data->cmd[0], env);
	if (!cmd_args)
		(printf("minishell: %s: No such file or directory\n", data->cmd[0]), exit(1));
	if (execve(cmd_args[0], data->cmd, env) == -1)
	{
		(perror("execve failed"), exit(1));
	}
    exit(127);
}

int	ft_len_struct(t_built *line_env)
{
	t_built *curr;
	int count;

	curr = line_env;
	count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char **ft_fill_envp(t_built *line_env)
{
	t_built *curr;
	char **envp;
	char *temp;
	int i;
	int len;

	len = ft_len_struct(line_env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	curr = line_env;
	i = 0;
	while (curr)
	{
		if (curr->value)
		{
			temp = ft_strjoin(curr->var, "=");
			if (!temp)
			{
				ft_free_split(envp);
				return (NULL);
			}
			envp[i] = ft_strjoin(temp, curr->value);
			free(temp);
			if (!envp[i])
			{
				ft_free_split(envp);
				return (NULL);
			}
			i++;
		}
		curr = curr->next;
	}
	envp[i] = NULL;
	return (envp);
}

void ft_exec(t_data *data, t_heredoc *heredoc, t_built *line_env)
{
	int		n_cmds;
	int		i;
	pid_t	pid;
	int		(*pipes)[2];
	t_built *curr;
	int flag_path;
	int flag_redir;
	char **envp;

	if (envp)
		envp = ft_fill_envp(line_env);
	curr = line_env;
	flag_path = 0;
	while (curr)
	{
		if (ft_strcmp(curr->var, "PATH") == 0)
			flag_path = 1;
		else if (curr->next == NULL && ft_strcmp(curr->var, "PATH") == 0)
			flag_path = 0;
		curr = curr->next;
	}
	if (flag_path == 1)
	{
		i = 0;
		flag_redir = ft_flag_redir(data);
		n_cmds = ft_count_cmds(data);
		pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
		if (!pipes)
			return ;
		while (i < n_cmds - 1)
			if (pipe(pipes[i++]) == -1)
				(perror("Pipe creation failed"), exit(1));
		if (data->type == 0 && flag_redir == 0)
		{
			i = 0;
			while (i < n_cmds)
			{
				pid = fork();
				if (pid == -1)
					(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
					ft_child_pro(data, pipes, i, n_cmds, envp);
				data = data->next;
				i++;
			}
			ft_close_pipes(pipes, n_cmds);
			while (wait(NULL) > 0);
			free(pipes);
		}
		else if (data->type == 1 || flag_redir == 1)
		{
			char *command = ft_check_built_redir(data, envp);
			if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
			{
				i = 0;
				while (i < n_cmds)
				{
					pid = fork();
					if (pid == -1)
						(ft_close_pipes(pipes, n_cmds), perror("Fork failed"), exit(1));
					else if (pid == 0)
						ft_child_pro(data, pipes, i, n_cmds, envp);
					data = data->next;
					i++;
				}
				ft_close_pipes(pipes, n_cmds);
				while (wait(NULL) > 0);
				free(pipes);
			}
			if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
			{
				ft_is_builtins(data, line_env, envp);
			}
			if (flag_redir == 1)
			{
				ft_is_redir(data, envp, heredoc);
			}
		}
	}
	else
	{
		n_cmds = ft_count_cmds(data);
		pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
		while (i < n_cmds - 1)
			pipe(pipes[i++]);
		i = 0;
		while (i < n_cmds)
		{
			pid = fork();
			if (pid == 0)
				ft_child_pro_f(data, pipes, i, n_cmds, envp, line_env, heredoc);
			data = data->next;
			i++;
		}
		ft_close_pipes(pipes, n_cmds);
		while (wait(NULL) > 0);
		free(pipes);
	}
}
