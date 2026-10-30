/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:55:43 by yael-oua          #+#    #+#             */
/*   Updated: 2025/08/07 10:23:04 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../execution/execution.h"

typedef struct s_parsing
{
	char	**s;
	t_data	*end;
	char	*str;
}	t_parsing;

typedef struct s_norm
{
	char	**s;
	int		i;
	int		k;
}	t_norm;

typedef struct s_less
{
	t_data	*curr;
	t_data	*node;
}	t_less;

typedef struct s_expanding
{
	char	*s;
	int		i;
	int		start;
	char	*tmp;
}	t_expanding;

typedef struct s_tokenizing
{
	int		quote_len;
	int		st;
	char	cha;
}	t_tokenize;

typedef struct s_retokenize
{
	int		i;
	char	*quoted;
	char	*token;
	char	**split;
}	t_retokenize;

int				is_o(char c);
char			*get_token(char *str, int *i);
int				count_tokens(char *str);
char			**tokenize(char *str);

char			*getinput(char *s, int *status, int *flag);
int				semifflag(char **s);
char			*get_last_cmd(char **s);
void			handle_signal(void);
void			handler(int signum);
t_built			*ft_in_l_ev(t_built *line_env, char **env);
int				check_before(char *s);
int				syntax_error(char **s);

char			**ft_subarray(char **tokens, int start, int end);
char			*ft_subpar(char *s, int start, int len);
char			**ft_joinarray(char **s1, char **s2);
char			**ft_split_par(char *str, char c);
int				mp(char *s1, char *s2);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				token_len(char **tokens);
char			*ft_strjoin_par(char *s1, char *s2);

char			*get_env_value(char *var, t_built *env);
char			*expanding(char *s, t_built *env, t_exec *in);
char			*expanding_heredoc(char *s, t_built *env, t_exec *in);
char			*exp_target(char *s, t_built *env, t_exec *in);
char			*extract_target(char *str, int i, t_built *env, t_exec *in);
char			*extract_quoates(char *str, int i);

t_data			*part1(char **s, t_built *env, t_exec *in);
int				semiflag(char *s);
char			**command(char **s, int i, int k);
t_redir			*creatn2(t_norm *norm, t_built *env, t_exec *in);
int				check_red(char **s, int i, int k);
t_type_redir	check_redirection(char *token);
t_redir			*create_redir_node(t_type_redir type,
					char *target, t_built *env, t_exec *in);
int				find_pipe(char **s);

char			*extract_retoken(char *str, int i, t_built *env, t_exec *in);
t_data			*retokenize(t_data *data, t_built *env, t_exec *in);
int				lookfor_ex(char *s);
char			*wrap_assignment_value(char *s, int val_start);
int				check_space(char *s);

void			freedp(char **tokens);

#endif