/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:27 by akahir            #+#    #+#             */
/*   Updated: 2025/06/17 15:17:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


// this working just for builtins.
typedef struct s_built
{
	char *var;
	char *value;
	struct s_built *next;
} t_built;


typedef struct s_heredoc
{
	int before_hered; // example : (cmd << EOF) or (cmd1 | cmd2 << EOF)
	int after_hered;  // example : (<< EOF cmd) or (<< EOF cmd1 | cmd2)
	int middle_hered; // example : (cmd << EOF cmd) or (cmd1 | cmd2 << EOF cmd1 | cmd2)
} t_heredoc;

typedef enum s_type_node
{
	PIPE_NODE,
	CMD_NODE
}	t_type_node;

typedef enum s_type_redir
{
	NOT_REDIR = -1,
	TRUNCATE,  // > Redirects standard output to a file, overwriting the file if it exists.
	APPEND,    // >> Redirects standard output to a file, appending to the file if it exists.
	READ_F,    // < Redirects a file as standard input to a command.
	HEREDOC    // << Tells the shell to read input until a specific delimiter is reached.
}	t_type_redir;

typedef struct s_redir
{
	t_type_redir type;
	char *target;
	struct s_redir *next;
}	t_redir;

typedef enum s_type_buil
{
	NOT_BUILTIN = -1,
	IS_ECHO,
	IS_CD,
	IS_PWD,
	IS_EXPORT,
	IS_UNSET,
	IS_ENV,
	IS_EXIT
}	t_type_buil;

typedef struct s_data
{
	t_type_node type; // if i have a pipe you need to give me type->PIPE_NODE else if he is a builtin or just a cmd = type->CMD_NOED
	t_redir *redir;           // redirection list
	t_type_buil builtin_type; // store the builtin directly (not in a substruct)
	char **cmd;               // {"cd", "cat", "-e",  "Documents", "builtins", NULL}
	struct s_data *next;
}	t_data;

// *****************prin funcl*****************
void ft_exec(t_data *data, char **env, t_heredoc *heredoc);
void	ft_child_pro(t_data *curr, int pipes[][2], int i, int n_cmds, char **env);

// *****************builtins func**************
void ft_is_builtins(t_data *data, char **env);
void ft_echo(char **str);
void ft_cd(char **str);
void ft_pwd(char **str);
//export
void	ft_unset(char **args, char ***env);
void	ft_env(char **str, char **env);
void ft_exit(char **str);


// **************redirections func*************
void ft_is_redir(t_data *data, char **env, t_heredoc *heredoc);
void ft_tran_app(t_data *data, t_data *curr, int flag, char **env);
void ft_read_f(t_data *data, t_data *curr, int flag, char **env);
// -> heredoc :
int ft_handle_heredoc(char *del);
		// -> heredoc before:
void    ft_heredoc_before(t_data *data, char **env);
void	ft_child_hered_bef(t_data *curr, int pipes[][2], int i, int n_cmds, int *hered_fd, char **env);
		// -> heredoc after :
void ft_heredoc_after(t_data *data, char **env);
void ft_child_hered_aft(t_data *curr, int pipes[][2], int i, int n_cmds, int *hered_fd, char **env);
		// -> heredoc middle :
void ft_handle_middle(t_data *data, char **env);
void ft_child_hered_midd(t_data *curr, int pipes[][2], int i, int n_cmds, char **env);

// **************func execution*****************
char	**ft_get_path(char *cmd, char **env);
int ft_flag_redir(t_data *data);

// ***************utils execution****************** 
void ft_close_pipes(int pipes[][2], int n_cmds);
int ft_count_cmds(t_data *cmd);
void	free_split(char **split);
char *ft_check_built_redir(t_data *data, char **env);

// ******************Libft func******************
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int	ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);
char	*ft_strdup(char *s1);
int	ft_strncmp(char *s1, char *s2, size_t n);
int	ft_atoi(const char *str);

#endif