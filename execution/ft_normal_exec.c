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
	t_data *tmp;

	tmp = data;
	status = 0;
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &g_orig_term);
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
				return (ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), 1);
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
		tmp = data;
		for (int j = 0; j < in.n_cmds - 1; j++)
		{
			if (tmp && tmp->next)
				tmp = tmp->next;
		}
		int flag_interactive = 0;
		if (tmp && tmp->cmd && tmp->cmd[0])
		{
			if (ft_strcmp(tmp->cmd[0], "top") == 0 || ft_strcmp(tmp->cmd[0], "wc") == 0)
				flag_interactive = 1;
		}
		pid_t ch_pid;
		int final_status = 0;
		int signal_printed = 0;
		while ((ch_pid = wait(&status)) > 0)
		{
			if (isatty(0))
				tcsetattr(0, TCSANOW, &g_orig_term);
			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
				{
					if (!signal_printed)
					{
						if (flag_interactive)
							write(1, "\n", 1);
						else
							write(1, "^C\n", 3);
						signal_printed = 1;
					}
					if (ch_pid == last_pid)
						final_status = 130;
				}
				else if (sig == SIGQUIT)
				{
					if (!signal_printed)
					{
						if (flag_interactive)
							write(1, "^\\\n", 4);
						else
							write(1, "^\\Quit: 3\n", 11);
						signal_printed = 1;
					}
					if (ch_pid == last_pid)
						final_status = 131;
				}
				else
				{
					if (ch_pid == last_pid)
						final_status = 128 + sig;
				}
			}
			else if (WIFEXITED(status) && ch_pid == last_pid)
			{
				final_status = WEXITSTATUS(status);
			}
		}
		status = final_status;
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
					return (ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), 1);
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
				if (isatty(0))
					tcsetattr(0, TCSANOW, &g_orig_term);
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
