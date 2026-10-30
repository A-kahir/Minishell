/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:22:15 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/29 15:28:18 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getinput(char *s, int *status, int *flag)
{
	char	*buff;

	buff = readline("minishell-3.2$ ");
	if (g_status == 1)
	{
		*status = 1;
		*flag = 1;
		g_status = 0;
	}
	if (!buff)
	{
		write(1, "exit\n", 5);
		malloc_cl(0, 3, 0);
		exit(*status);
	}
	if (*buff && buff[0] != '\n')
	{
		add_history(buff);
		s = ft_strdup(buff, 0, 0);
		free(buff);
		return (s);
	}
	free(buff);
	return (s);
}

int	semifflag(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			return (1);
		i++;
	}
	return (0);
}

char	*get_last_cmd(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] == NULL)
			break ;
		i++;
	}
	return (ft_strdup(s[i], 0, 1));
}

void	handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

t_built	*ft_in_l_ev(t_built *line_env, char **env)
{
	static int	one_time;

	if (!line_env && one_time == 0)
	{
		if (!env || !env[0] || ft_empty_env(env))
			line_env = ft_no_full_env(line_env);
		else
			line_env = ft_fill_struct(env);
		if (line_env)
			line_env = ft_update_exp(line_env, 0);
		one_time = 1;
	}
	return (line_env);
}
