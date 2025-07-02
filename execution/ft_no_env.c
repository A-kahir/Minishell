/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:19:21 by akahir            #+#    #+#             */
/*   Updated: 2025/06/29 15:19:21 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_no_env(t_data *data, t_ex_othr env_here, t_built *line_env, t_exec stat)
{
	pid_t	pid;
	t_exec	in;
	int		flag_redir;
	int		status;
	char *command;

	status = 0;
	ft_no_full_env(line_env);
	if (in.status)
		in.status = ft_strdup(stat.status);
	env_here.env = ft_fill_envp(line_env);
	command = ft_check_built_redir(data);
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return (0);
	int i = 0;
	while (i < in.n_cmds - 1)
		if (pipe(in.pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, line_env, env_here, in);
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		waitpid(pid, &status, 0);
		status = status / 256;
		free(in.pipes);
	}
	if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		ft_is_builtins(data, line_env, in);
	if (flag_redir == 1)
		ft_is_redir(data, line_env, env_here, stat);
	free(in.status);
	return (status);
}
