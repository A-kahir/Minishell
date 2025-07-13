/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/12 15:25:41 by akahir           ###   ########.fr       */
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
	
	buff = readline("minishell-3.2$~ ");
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
		if(s[i] == '$')
		return(1);
		i++;
	}
	return(0);
}
void re_do(t_data *end, t_built	*env)
{
	t_data *tmp = end;
	while (tmp)
	{
		if (tmp->cmd)
		{
			int count = 0;
			while (tmp->cmd[count])
				count++;
			int total_tokens = 0;
			int j = 0;
			while (j < count)
			{
				char *arg = tmp->cmd[j];
				int has_quotes = (ft_strchr(arg, '\'') || ft_strchr(arg, '\"'));
				if (has_quotes)
				{
					total_tokens++;
				}
				else
				{
					char **tokens = tokenize(arg, env);
					int k = 0;
					while (tokens && tokens[k])
					{
						total_tokens++;
						k++;
					}
					freedp(tokens);
				}
				j++;
			}
			char **new_cmd = malloc((total_tokens + 1) * sizeof(char *));
			int idx = 0;
			j = 0;
			while (j < count)
			{
				char *arg = tmp->cmd[j];
				int has_quotes = (ft_strchr(arg, '\'') || ft_strchr(arg, '\"'));
				if (has_quotes)
				{
					new_cmd[idx++] = ft_strdup(arg);
				}
				else
				{
					char **tokens = tokenize(arg, env);
					int k = 0;
					while (tokens && tokens[k])
					{
						new_cmd[idx++] = ft_strdup(tokens[k]);
						k++;
					}
					freedp(tokens);
				}
				j++;
			}
			new_cmd[idx] = NULL;
			freedp(tmp->cmd);
			tmp->cmd = new_cmd;
		}
		tmp = tmp->next;
	}
}
// int main(int ac, char **av, char **env)
// {
// 	char	**s;
// 	t_data	*end;
// 	char *string;
// 	static t_built *line_env;
// 	int i = 0;
// 	t_heredoc *heredoc;

// 	string = NULL;
// 	end = NULL;
// 	initsh();
// 	// signal(SIGINT, handler);
// 	if (!line_env)
// 	{
// 		line_env = ft_fill_struct(env);
// 		line_env = ft_update_exp(line_env, 0); 
// 	}
// 	while(1)
// 	{
// 		string = getinput(string);
// 		if(!string)
// 			continue;
// 		if(check_before(string))
// 		{
// 			string = NULL;
// 			continue;
// 		}
// 		// string = expand_dollar(string, line_env);
// 		// printf("%s\n", string);
// 		s = tokenize(string, line_env);
// 		if(!syntax_error(s))
// 		{
// 			string = NULL;
// 			freedp(s);
// 			continue;
// 		}
// 		end = part1(s);
// 		// t_data *tmp = end;
// 		// re_do(end, line_env);
// 		freedp(s);
// 		heredoc = malloc(sizeof(t_heredoc));
// 		detect_heredoc_position(end, heredoc, string);
// 		if (heredoc->middle_hered)
// 			merge_middle_heredoc_cmd(end);
// 		// ft_exec(end, env, heredoc, line_env);
// 		n_clean(end);
// 		free(heredoc);
// 		free(string);
// 		string = NULL;
// 	}
// 	return 0;
// }


int main(int ac, char **av, char **env)
{
		char	**s;
		t_data	*end;
		char *string;
		static t_built *line_env;
		// int i = 0;
		t_heredoc *heredoc;
		t_exec in;
    	static int status;
	
	(void)ac;
	(void)av;
	string = NULL;
	end = NULL;
	initsh();
	// signal(SIGINT, handler);
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
		// string = expand_dollar(string, line_env);
		// printf("%s\n", string);
		// printf("im here\n");
		s = tokenize(string, line_env);
		if(!syntax_error(s))
		{
			string = NULL;
			freedp(s);
			continue;
		}
		// printf("im here2\n");
		// printf("%s\n", s[0]);
		// printf("%s\n", s[1]);
		end = part1(s);
		// t_data *tmp = end;
		// re_do(end, line_env);
		freedp(s);
		heredoc = malloc(sizeof(t_heredoc));
		detect_heredoc_position(end, heredoc, string);
		if (heredoc->middle_hered)
			merge_middle_heredoc_cmd(end);
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
		if (end && end->cmd[0] && (end->cmd[0][0] >= '0' && end->cmd[0][0] <= '9'))
		{
			printf("in main\n");
			write(2, "minishell: ", 11);
			write(2, end->cmd[0], ft_strlen(end->cmd[0]));
			write(2, ": command not found\n", 21);
			free(in.status);
			in.status = ft_strdup("127");
		}
		else
		{
			if (end && end->cmd && end->cmd[0] && end->cmd[1] &&
				ft_strcmp(end->cmd[0], "env") == 0 && ft_strcmp(end->cmd[1], "-i") == 0)
			{
				ft_clean_env(&line_env);
			}
			else
			{
				status = ft_exec(end, heredoc, line_env, in);
			}
		}
		flag = 1;
		n_clean(end);
		free(heredoc);
		free(string);
		string = NULL;
	}
	return 0;
}
