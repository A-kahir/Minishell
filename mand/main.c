/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/16 21:11:23 by akahir           ###   ########.fr       */
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
    {
        write(1, "\033[1A\033[16C", 9);
        write(1, "exit\n", 5);
        exit(0);
    } 
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

static void handler()
{
	printf("\n");
	// write(1, "\n", 1);
 	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	static int flag;
	
	(void)ac;
	(void)av;
	string = NULL;
	end = NULL;
	initsh();
	disable_echoctl();
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	static int one_time;
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
	while(1)
	{
		string = getinput(string);
		if(!string)
			continue;
		if(check_before(string))
		{
			status = 258;
			flag = 1;
			free(string);
			string = NULL;
			continue;
		}
		s = tokenize(string);
		if(syntax_error(s) != 1)
		{
			status = 258;
			flag = 1;
			free(string);
			string = NULL;
			freedp(s);
			continue;
		}
		end = part1(s, line_env);
		t_data *tmpa = retokenize(end, line_env);
		// t_data *tmp22 = end;
        // while (tmp22)
        // {
        //     int i = 0;
        //     printf("START OF A NODE\n");
        //     printf("type_node === %d\n", tmp22->type);
        //     while(tmp22->redir)
        //     {
        //         printf("type=== %d\n", tmp22->redir->type);
        //         printf("target=== %s\n", tmp22->redir->target);
        //         tmp22->redir = tmp22->redir->next;
        //     }
        //     while (tmp22->cmd[i])
        //     {
        //         printf("cmd[%d]---> %s \n", i, tmp22->cmd[i]);
        //         i++;    
        //     }
        //     tmp22 = tmp22->next;
        // }
		freedp(s);
		heredoc = malloc(sizeof(t_heredoc));
		detect_heredoc_position_with_pipes(end, heredoc);
		t_data *curr = end;
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
        char *tmp = ft_strdup(ft_itoa(status));
        in.status = ft_strdup(tmp);
        free(tmp);
		if (end && end->cmd && end->cmd[0] && end->cmd[1] &&
			ft_strcmp(end->cmd[0], "env") == 0 && ft_strcmp(end->cmd[1], "-i") == 0
			&& ft_strcmp(end->cmd[2], "./minishell") == 0)
		{
			ft_clean_env(&line_env);
		}
		else if (end && end->cmd && end->cmd[0] && end->cmd[1] &&
			ft_strcmp(end->cmd[0], "env") == 0 && (ft_strcmp(end->cmd[1], "-i") != 0
			|| ft_strcmp(end->cmd[2], "./minishell") != 0))
		{
			write(2, "minishell: ", 12);
			write(2, "env: No such file or directory\n", 32);
			status = 127;
		}
		else
		{
			status = ft_exec(end, heredoc, line_env, in);
		}
		flag = 1;
		n_clean(end);
		free(heredoc);
		free(string);
		free(in.status);
		string = NULL;
	}
	return 0;
}
