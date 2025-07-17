/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:55:43 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/17 14:06:23 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
// #include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <termios.h>
#include"../execution/execution.h"


// typedef struct s_heredoc
// {
// 	int before_hered; // example : (cmd << EOF) or (cmd1 | cmd2 << EOF)
// 	int after_hered;  // example : (<< EOF cmd) or (<< EOF cmd1 | cmd2)
// 	int middle_hered; // example : (cmd << EOF cmd) or (cmd1 | cmd2 << EOF cmd1 | cmd2)
// } t_heredoc;

// typedef enum s_type_node
// {
// 	PIPE_NODE,
// 	CMD_NODE
// }	t_type_node;

// typedef enum s_type_redir
// {
// 	NOT_REDIR = -1,
// 	TRUNCATE,  // > Redirects standard output to a file, overwriting the file if it exists.
// 	APPEND,    // >> Redirects standard output to a file, appending to the file if it exists.
// 	READ_F,    // < Redirects a file as standard input to a command.
// 	HEREDOC    // << Tells the shell to read input until a specific delimiter is reached.
// }	t_type_redir;

// typedef struct s_redir
// {
// 	t_type_redir type;
// 	char *target;
// 	struct s_redir *next;
// }	t_redir;

// typedef enum s_type_buil
// {
// 	NOT_BUILTIN = -1,
// 	IS_ECHO,
// 	IS_CD,
// 	IS_PWD,
// 	IS_EXPORT,
// 	IS_UNSET,
// 	IS_ENV,
// 	IS_EXIT
// }	t_type_buil;

// typedef struct s_data
// {
// 	t_type_node type; // if i have a pipe you need to give me type->PIPE_NODE else if he is a builtin or just a cmd = type->CMD_NOED
// 	t_redir *redir;           // redirection list
// 	t_type_buil builtin_type; // store the builtin directly (not in a substruct)
// 	char **cmd;               // {"cd", "cat", "-e",  "Documents", "builtins", NULL}
// 	struct s_data *next;
// }	t_data;


typedef struct s_cmd {
	char	**s;
	int		not_pipe; 
} t_cmd;

int		is_operator(char c);
char	**tokenize(char *str);

int	check_before(char *s);
int	syntax_error(char **s);

// size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
// char	*ft_strdup(const char *src);
char	**ft_subarray(char **tokens, int start, int end);
char	*ft_substr_par(char *s, unsigned int start, size_t len);
char	**ft_strjoinarray(char **s1, char **s2);
char    *ft_rejoin(int size, char **strs, char *sep);
char	**ft_split_par(char *str, char c);
char	**redo(char **s, t_built *env);
// int		ft_strcmp(const char *s1, const char *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);

char *get_env_value(char *var, t_built *env);
char	*expanding_target(char *s, t_built *env);
char	*extract_target(char *str, int i, t_built *env);
char	*extract_quoates(char *str, int i);

void    detect_heredoc_position_with_pipes(t_data *d, t_heredoc *h);
void    detect_heredoc_position(t_data *d, t_heredoc *h);
void    merge_middle_heredoc_cmd(t_data *d);

t_data	*part1(char **s, t_built *env);
int	semiflag(char *s);
char	*extract_retoken(char *str, int i, t_built *env);
t_data *retokenize(t_data *data, t_built *env);
char	**join_zmr(char *s1, char *s2);

void	f_clean(char *s);
void	n_clean(t_data *n);
void freedp(char **tokens);
void	freenod(t_data *n);

int		token_len(char **tokens);
// char	*extract_token(char *str, int *i);
char	*ft_strjoin_par(char *s1, char *s2);
int	does_it_exist(char *s, t_built *env);
// char *get_value_from_env(const char *key, t_built *env);
// char *expand_dollar(char *input, t_built *env);
char *expanding(char *s, t_built *env);



int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
size_t	ft_strcspn(const char *s, const char *reject);


#endif