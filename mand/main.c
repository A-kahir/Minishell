/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:57 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/04 13:41:06 by akahir           ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
	char	**s;
	t_data	*end;
	char *string;
	static t_built *line_env;
	int i = 0;
	t_heredoc *heredoc;
	t_exec in;
    static int status;
	
	string = NULL;
	end = NULL;
	initsh();
	// signal(SIGINT, handler);
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
		
		end = part1(s);
		// i = 0;
		// while(s[i])
		// {
		// 	printf("smd[%d]--->%s\n", i, s[i]);
		// 	i++;
		// }
		freedp(s);
		heredoc = malloc(sizeof(t_heredoc));
		detect_heredoc_position(end, heredoc, string);
		if (heredoc->middle_hered)
			merge_middle_heredoc_cmd(end);
		if (!line_env)
		{
			line_env = ft_fill_struct(env);
			line_env = ft_update_exp(line_env, 0); 
		}
        t_data *curr = end;
        static int flag;
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
            curr = curr->next;
        }
        char *tmp = ft_itoa(status);
        in.status = ft_strdup(tmp);
        free(tmp);
		// epxand_tokens();
		
		status = ft_exec(end, heredoc, line_env, in);
		n_clean(end);
		free(heredoc);
		free(string);
		string = NULL;
	}
	return 0;
}
