/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:04:41 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:04:41 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_exec_normal(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	pid_t	pid;
	t_exec	in;
	int		flag_redir;
	int		status;
	int		last_status;

	status = 0;
	in.status = ft_strdup(stat.status);
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (free(in.status), 0);
	int i = 0;
	while (i < in.n_cmds - 1)
		if (pipe(in.pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	pid_t last_pid = 0;
	if (data->type == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				ft_child_pro(data, line_env, env_here, in);
			}
			else
			{
				if (in.i == in.n_cmds - 1)
            		last_pid = pid;
			}
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		pid_t ch_pid;
		int f_status = 0;
		int nb = 0;
		while ((ch_pid = wait(&status)) > 0)
		{
			if (WIFSIGNALED(status) && ch_pid != last_pid)
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(1, "^C\n", 4);
					f_status = 0;
				}
				else if(WTERMSIG(status) == SIGQUIT)
				{
					write(1, "^\\", 3);
					f_status = 0;
				}
				if (nb)
					f_status = nb;
			}
			else if (ch_pid == last_pid)
			{
				if (WIFEXITED(status))
					f_status = WEXITSTATUS(status);
				nb = f_status;
			}
		}
		status = f_status;
		free(in.pipes);
	}
	else if (data->type == 1 || flag_redir == 1)
	{
		char *command = ft_check_built_redir(data);
		if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
		{
			in.i = 0;
			while (in.i < in.n_cmds)
			{
				pid = fork();
				
				if (pid == -1)
					(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
				else if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					ft_child_pro(data, line_env, env_here, in);
				}
				else
				{
					if (in.i == in.n_cmds - 1)
						last_pid = pid;
				}
				data = data->next;
				in.i++;
			}
			ft_close_pipes(in.pipes, in.n_cmds);
			pid_t ch_pid;
			int f_status = 0;
			while ((ch_pid = wait(&status)) > 0)
			{
				if (ch_pid == last_pid)
				{
					if (WIFSIGNALED(status))
					{
						if (WTERMSIG(status) == SIGINT)
						{
							write(1, "^C\n", 4);
							f_status = 128 + SIGINT;
						}
						else if(WTERMSIG(status) == SIGQUIT)
						{
							write(1, "^\\Quit: 3\n", 11);
							f_status = 128 + SIGQUIT;
						}
						else
						{
							f_status = 128 + WTERMSIG(status);
						}
					}
					else if (WIFEXITED(status))
					{
						f_status = WEXITSTATUS(status);
					}
				}
			}
			status = f_status;
			free(in.pipes);
		}
		if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		{
			status = ft_is_builtins(data, line_env, in);
		}
		if (flag_redir == 1)
			status = ft_is_redir(data, line_env, env_here, stat);
	}
	return (status);
}
