/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/14 14:41:23 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear(void)
{
	printf("\033[H\033[J");
}

void	initsh(void)
{
	clear();
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****WELCOME****");
	printf("\n\n\n\n*******************"
		"***********************");
	sleep(1);
	clear();
}

char	*getinput(char *s)
{
	char	*buff;
	
	buff = readline("minishell-3.2$ ");
	if (!buff)
		f_clean(buff);
	if (*buff)
	{
		add_history(buff);
		s = ft_strdup(buff);
		free(buff);
		return(s);
	}
	free(buff);
	return(s);
}

int	semifflag(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if(s[i] == '$' && !ft_strchr(s, '=') && (!ft_strchr(s, '\"') || !ft_strchr(s, '\'')))
		return(1);
		i++;
	}
	return(0);
}

void handler()
{
	printf("\n");
	// write(1, "\n", 1);
 	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
 }
void handler2()
{
	printf("exit\n");
	// write(1, "\n", 1);
	exit(0);
 	// rl_on_new_line();
 }

 
int main(int ac, char **av, char **env)
{
		char	**s;
		t_data	*end;
		char *string;
		static t_built *line_env;
		t_heredoc *heredoc;
		t_exec in;
    	static int status;
	
	(void)ac;
	(void)av;
	string = NULL;
	end = NULL;
	initsh();
	signal(SIGINT, handler);
	signal(SIGQUIT, handler2);
	static int one_time;
	if (!line_env && one_time == 0)
	{
		if (env == NULL || env[0] == NULL)
			line_env = NULL;
		else if (ft_empty_env(env))
			line_env = NULL;
		else
			line_env = ft_fill_struct(env);
		if (line_env)
			line_env = ft_update_exp(line_env, 0);
		one_time = 1;
	}
	while(1)
	{
		string = getinput(string);
		if(!string)
			continue;
		if(check_before(string))
		{
			string = NULL;
			continue;
		}
		s = tokenize(string);
		if(!syntax_error(s))
		{
			string = NULL;
			freedp(s);
			continue;
		}
		end = part1(s, line_env);
		t_data *tmpa = retokenize(end, line_env);
		// t_data *tmp22 = end;
		// while (tmp22)
		// {
		// 	int i = 0;
		// 	printf("START OF A NODE\n");
		// 	printf("type_node === %d\n", tmp22->type);
		// 	while(tmp22->redir)
		// 	{
		// 		printf("type=== %d\n", tmp22->redir->type);
		// 		printf("target=== %s\n", tmp22->redir->target);
		// 		tmp22->redir = tmp22->redir->next;
		// 	}
		// 	while (tmp22->cmd[i])
		// 	{
		// 		printf("cmd[%d]---> %s \n", i, tmp22->cmd[i]);
		// 		i++;	
		// 	}
		// 	tmp22 = tmp22->next;
		// }
		freedp(s);
		heredoc = malloc(sizeof(t_heredoc));
		detect_heredoc_position_with_pipes(end, heredoc);
		t_data *curr = end;
        static int flag;
        static int flag_fd;
        while (curr)
        {
            if (curr->cmd && curr->cmd[0] && ft_strcmp(curr->cmd[0], "$?") == 0)
            {
                free(curr->cmd[0]);
                if (flag == 0)
                {
                    curr->cmd[0] = ft_strdup("0");
                    flag = 1;
                }
                else if (flag == 1)
                {
                    curr->cmd[0] = ft_strdup(ft_itoa(status));
                }
            }
			else if (curr->redir && curr->redir->type != 3 &&  curr->redir->target && ft_strcmp(curr->redir->target, "$?") == 0)
			{
				free(curr->redir->target);
				if (flag_fd == 0)
				{
					curr->redir->target = ft_strdup("0");
					flag_fd = 1;
				}
				else if (flag_fd == 1)
				{
					curr->redir->target = ft_strdup(ft_itoa(status));
				}
			}
            curr = curr->next;
        }
        char *tmp = ft_itoa(status);
        in.status = ft_strdup(tmp);
        free(tmp);
		if (end && end->cmd && end->cmd[0] && end->cmd[1] &&
			ft_strcmp(end->cmd[0], "env") == 0 && ft_strcmp(end->cmd[1], "-i") == 0)
		{
			ft_clean_env(&line_env);
		}
		else
		{
			status = ft_exec(end, heredoc, line_env, in);
		}
		flag = 1;
		n_clean(end);
		free(heredoc);
		free(string);
		string = NULL;
	}
	return 0;
}
