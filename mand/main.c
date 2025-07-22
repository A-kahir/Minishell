/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/22 15:22:25 by yael-oua         ###   ########.fr       */
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

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*getinput(char *s, int *status, int *flag)
{
	char	*buff;
	buff = readline("minishell-3.2$ ");
	if (!buff)
    {
        write(1, "exit\n", 5);
        exit(*status);
    }
	if (g_status)
	{
		*status = 1;
		*flag = 1;
		g_status = 0;
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

int	semifflag(char **s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "|"))
			return(1);
		i++;
	}
	return(0);
}
char	*get_last_cmd(char **s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (s[i + 1] == NULL)
			break ;
		i++;
	}
	return(ft_strdup(s[i]));
}

static void handler(int signum)
{
	(void)signum;
	printf("\n");
 	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
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
	static char	*last_cmd;
	
	if(isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
        exit(1); 
	last_cmd = ft_strdup("mini");
	(void)ac;
	(void)av;
	string = NULL;
	end = NULL;
	initsh();
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
	disable_echoctl();
	while(1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		string = getinput(string, &status, &flag);
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
		if (semifflag(s))
			in.status = ft_itoa(0);
		else
			in.status = ft_itoa(status);
		end = part1(s, line_env, &in);
		t_data *tmpa = retokenize(end, line_env, &in);
		t_data *tmp22 = end;
		in.last_cmd = last_cmd;
		if(semifflag(s) || !tmp22->cmd)
		{
			// if(last_cmd)
			// 	free(last_cmd);
			last_cmd = ft_strdup("");
		}
		else
		{
			last_cmd = get_last_cmd(tmp22->cmd);
		}
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
		// t_data *curr = end;
        // static int flag_fd;
        // while (curr)
        // {
        //     if (curr->cmd && curr->cmd[0] && ft_strcmp(curr->cmd[0], "$?") == 0)
        //     {
        //         free(curr->cmd[0]);
        //         if (flag == 0)
        //         {
        //             curr->cmd[0] = ft_strdup("0");
        //             flag = 1;
        //         }
        //         else if (flag == 1)
        //             curr->cmd[0] = ft_itoa(status);
        //     }
		// 	else if (curr->redir && curr->redir->type != 3 &&  curr->redir->target && ft_strcmp(curr->redir->target, "$?") == 0)
		// 	{
		// 		free(curr->redir->target);
		// 		if (flag_fd == 0)
		// 		{
		// 			curr->redir->target = ft_strdup("0");
		// 			flag_fd = 1;
		// 		}
		// 		else if (flag_fd == 1)
		// 			curr->redir->target = ft_itoa(status);
		// 	}
        //     curr = curr->next;
        // }
        // char *tmp = ft_itoa(status);
        // in.status = ft_strdup(tmp);
        // free(tmp);
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
			ft_check_hered(end->redir);
			status = ft_exec(end, heredoc, line_env, in);
		}
		flag = 1;
		n_clean(end);
		free(heredoc);
		free(string);
		// free(in.status);
		free(last_cmd);
		string = NULL;
	}
	return (0);
}
