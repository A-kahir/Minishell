/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/03 17:02:55 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_part_execution(t_data *end, t_built *line_env, t_exec in)
{
	int	status;

	status = 0;
	if (end && end->cmd && end->cmd[0] && end->cmd[1] && end->cmd[2]
		&& !ft_strcmp(end->cmd[0], "env") && (ft_strcmp(end->cmd[1], "-i")
			|| ft_strcmp(end->cmd[2], "./minishell")))
	{
		write(2, "minishell: ", 12);
		write(2, "env: No such file or directory\n", 32);
		status = 127;
	}
	else
	{
		ft_check_hered(end->redir);
		status = ft_exec(end, line_env, in);
	}
	return (status);
}

t_data	*parsing(char **s, t_exec *in, int status, t_built *line_env)
{
	t_data	*end;
	t_data	*tmp22;

	end = NULL;
	if (semifflag(s))
		in->status = ft_itoa(0);
	else
		in->status = ft_itoa(status);
	end = part1(s, line_env, in);
	if (!end)
		return (malloc_cl(0, 1, 0), NULL);
	tmp22 = retokenize(end, line_env, in);
	if (semifflag(s) || !tmp22->cmd)
		in->last_cmd = ft_strdup("", 0, 1);
	else
		in->last_cmd = get_last_cmd(tmp22->cmd);
	return (end);
}

int	ft_cantiue(int *status, t_parsing *t, int *flag)
{
	if (check_before(t->str))
	{
		1 && (*status = 258, *flag = 1, t->str = NULL);
		return (1);
	}
	if (syntax_error(tokenize(t->str)) != 1)
	{
		1 && (*status = 258, *flag = 1, t->str = NULL, malloc_cl(0, 1, 0));
		return (1);
	}
	return (0);
}

int	ft_main_loop(t_built *l_ev, t_exec in, int *status, int *flag)
{
	t_parsing	t;

	t.str = NULL;
	while (1)
	{
		1 && (handle_signal(), t.str = getinput(t.str, status, flag));
		if (!t.str)
			continue ;
		if (ft_cantiue(status, &t, flag) == 1)
			continue ;
		t.end = parsing(tokenize(t.str), &in, *status, l_ev);
		if (!t.end)
		{
			t.str = NULL;
			continue ;
		}
		*status = ft_part_execution(t.end, l_ev, in);
		1 && (*flag = 1, malloc_cl(0, 1, 0), t.str = NULL);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	static t_built	*l_ev;
	t_exec			in;
	static int		status;
	static int		flag;

	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
		exit(1);
	(void)ac;
	(void)av;
	1 && (in.last_cmd = ft_strdup("mini", 0, 0), l_ev = ft_in_l_ev(l_ev, env));
	ft_main_loop(l_ev, in, &status, &flag);
	return (malloc_cl(0, 2, 0), 0);
}
