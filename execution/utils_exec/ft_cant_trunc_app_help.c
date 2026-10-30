/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cant_trunc_app_help.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:53:54 by akahir            #+#    #+#             */
/*   Updated: 2025/07/28 23:54:04 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_creat_pp(t_exec *in)
{
	in->i = 0;
	while (in->i < in->n_cmds - 1)
	{
		if (pipe(in->pipes[in->i]) == -1)
		{
			perror("pipe");
			return ;
		}
		in->i++;
	}
}

pid_t	ft_fork_child(t_data *tmp, t_built *line_env,
t_ex_othr env_here, t_exec *in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		ft_child_redir(tmp, line_env, env_here, *in);
	}
	return (pid);
}
