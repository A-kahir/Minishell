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

void ft_exec(t_data *data, t_heredoc *heredoc, t_built *line_env)
{
	int		n_cmds;
	int		i;
	pid_t	pid;
	int		(*pipes)[2];
	t_built *curr;
	int flag_path;
	int flag_redir;
	static int no_env;
	char **envp;

	i = 0;
	if ((ft_strcmp(line_env->var, "OLDPWD") == 0 && line_env->next == NULL) || no_env == 1)
	{
		no_env = 1;
		ft_no_full_env(line_env);
		envp = ft_fill_envp(line_env);
		i = 0;
		char *command = ft_check_built_redir(data);
		flag_redir = ft_flag_redir(data);
		n_cmds = ft_count_cmds(data);
		pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
		if (!pipes)
			return ;
		while (i < n_cmds - 1)
			if (pipe(pipes[i++]) == -1)
				(perror("Pipe creation failed"), exit(1));
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
			ft_is_builtins(data, line_env);
		}
		if (flag_redir == 1)
		{
			ft_is_redir(data, envp, heredoc);
		}
	}
	else if (no_env == 0)
	{
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
			flag_redir = ft_flag_redir(data);
			n_cmds = ft_count_cmds(data);
			pipes = malloc(sizeof(int[2]) * (n_cmds - 1));
			if (!pipes)
				return ;
			i = 0;
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
				char *command = ft_check_built_redir(data);
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
					ft_is_builtins(data, line_env);
				}
				if (flag_redir == 1)
				{
					ft_is_redir(data, envp, heredoc);
				}
			}
		}
		else if (flag_path == 0)
		{
			flag_redir = ft_flag_redir(data);
			char *command = ft_check_built_redir(data);
			if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
				printf("minishell: %s: No such file or directory\n", data->cmd[0]);
			if (ft_strcmp(command, "built") == 0 && data->builtin_type != -1 && data->builtin_type != 5)
				ft_is_builtins_f(data, line_env);
			if (ft_flag_redir(data) == 1)
				ft_is_redir(data, envp, heredoc);
		}
	}
}
