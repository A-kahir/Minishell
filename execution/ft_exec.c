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

int ft_have_env(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
	int		flag_path;
	int		status;
	t_built *curr;

	env_here.env = ft_fill_envp(line_env);
	status = 0;
	flag_path = 0;
	curr = line_env;
	while (curr)
	{
		if (ft_strcmp(curr->var, "PATH") == 0)
			flag_path = 1;
		else if (curr->next == NULL && ft_strcmp(curr->var, "PATH") == 0 && ft_strcmp(curr->value, NULL) != 0)
			flag_path = 0;
		curr = curr->next;
	}
	if (flag_path == 1)
		status = ft_exec_normal(data, env_here, line_env, stat);
	else if (flag_path == 0)
		status = ft_if_un_path(data, env_here, line_env, stat);
	ft_free_split(env_here.env); 
	return (status);
}

void	debug_data(t_data *data)
{
	t_data *tmp = data;
	t_redir *redir;
	int i;

	while (tmp)
	{
		printf("======== NEW t_data NODE ========\n");

		// 1) Node type
		printf("1) tmp->type ===> %d\n", tmp->type);

		// 2) Builtin type (can be 0 if not builtin)
		printf("2) tmp->builtin_type ===> %d\n", tmp->builtin_type);

		// 3) Command array
		if (tmp->cmd)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				printf("3.%d) tmp->cmd[%d] ===> %s\n", i + 1, i, tmp->cmd[i]);
				i++;
			}
		}
		else
			printf("3) tmp->cmd ===> NULL\n");

		// 4) Redirections
		redir = tmp->redir;
		if (redir)
		{
			printf("=======> REDIRECTIONS <=======\n");
			while (redir)
			{
				printf("- redir->type ===> %d\n", redir->type);
				if (redir->target)
					printf("- redir->target ===> %s\n", redir->target);
				else
					printf("- redir->target ===> NULL\n");

				if (redir->next)
					printf("******* NEXT REDIR NODE ********\n");
				redir = redir->next;
			}
		}
		// else
		// 	printf("No redirections for this node.\n");

		if (tmp->next)
			printf("******** NEXT DATA NODE ********\n");

		tmp = tmp->next;
	}
}

int ft_exec(t_data *data, t_heredoc *heredoc, t_built *line_env, t_exec stat)
{
	t_ex_othr env_here;
	static int no_env = 0;
	int status = 0;
	t_built *curr = line_env;
	t_data *tmp;

	env_here.heredoc = heredoc;
	// debug_data(data);
	int count = 0;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	if ((count == 3) || no_env == 1)
	{
		no_env = 1;
		status = ft_no_env(data, env_here, line_env, stat);
	}
	else if (no_env == 0)
	{
		status = ft_have_env(data, line_env, env_here, stat);
	}
	ft_close_fd_opening();
	return (status);
}
