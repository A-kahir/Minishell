/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:27 by akahir            #+#    #+#             */
/*   Updated: 2025/08/07 10:22:44 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>

int	g_status;

# define PATH_ENV "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}	t_pid_list;

typedef enum e_mode
{
	ALLOCATE = 0,
	FREE_TEMP = 1,
	FREE_STRUCT = 2,
	FREE_ALL = 3
}	t_mode;

typedef struct s_leaks
{
	char			*ptr;
	struct s_leaks	*next;
}	t_leaks;

typedef struct s_exec
{
	int				i;
	int				n_cmds;
	int				(*pipes)[2];
	char			*status;
	char			*last_cmd;
	int				heredoc_flag_q;
	char			*reserve_norm;
	struct termios	g_orig_term;
}	t_exec;

typedef struct s_built
{
	char			*var;
	char			*value;
	char			*old_pwd;
	char			*pwd;
	struct s_built	*next;
}	t_built;

typedef struct s_ex_othr
{
	char	**env;
}	t_ex_othr;

typedef enum s_type_node
{
	PIPE_NODE,
	CMD_NODE
}	t_type_node;

typedef enum s_type_redir
{
	NOT_REDIR = -1,
	TRUNCATE,
	APPEND,
	READ_F,
	HEREDOC
}	t_type_redir;

typedef struct s_redir
{
	t_type_redir	type;
	char			*target;
	struct s_redir	*next;
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
	t_type_node		type;
	t_redir			*redir;
	t_type_buil		builtin_type;
	char			**cmd;
	struct s_data	*next;
}	t_data;

typedef struct s_pid
{
	pid_t	ch_pid;
	pid_t	last_pid;
}	t_pid;

// *****************prin funcl*****************
int			ft_exec(t_data *data, t_built *line_env, t_exec stat);
void		ft_child_pro(t_data *curr, t_built *line_env,
				t_ex_othr env_here, t_exec in);
int			ft_no_env(t_data *data, t_ex_othr env_here,
				t_built *line_env, t_exec stat);
int			ft_exec_normal(t_data *data, t_ex_othr env_here,
				t_built *line_env, t_exec stat);
int			ft_if_un_path(t_data *data, t_ex_othr env_here,
				t_built *line_env, t_exec stat);
// *****************builtins func**************
int			ft_is_builtins(t_data *data, t_built *line_env, t_exec in);
void		ft_echo(char **str);
char		*ft_pwd(t_built *line_env);
t_built		*ft_cd(char **str, t_built *line_env, int *flag_cd, t_exec *in);
t_built		*ft_export(t_built *line_env, char **cmd,
				int flag_one_pth, t_exec *in);
// -> func export :
void		ft_add_var(t_built *line_env, char *cmd);
void		ft_is_positif(t_built *line_env, char *cmd);

char		*ft_exit(t_data *data, t_exec *in);
t_built		*ft_unset(t_built *line_env, char **cmd, t_exec *in);
t_built		*ft_env(t_built *line_env, int flag_one_pth);

// **************redirections func*************
int			ft_is_redir(t_data *data, t_built *line_env,
				t_ex_othr env_here, t_exec stat);
int			ft_tran_app(t_data *data, t_built *line_env, t_ex_othr env_here);
int			ft_read_f(t_data *data, t_built *line_env, t_ex_othr env_here);
void		ft_child_read_f(t_data *curr, t_built *line_env,
				t_ex_othr env_here, t_exec in);
// -> heredoc :
int			ft_handle_heredoc(char *del, t_built *line_env, t_exec stat);
		// -> heredoc func:
int			ft_heredoc(t_data *data, t_built *line_env,
				t_ex_othr env_here, t_exec stat);
void		ft_child_heredoc(t_data *curr, t_built *line_env,
				t_ex_othr env_here, t_exec in);

// **************func execution*****************
char		**ft_get_path(char *cmd, char **env);
int			ft_flag_redir(t_data *data);

// ***************utils execution****************** 
void		ft_close_pipes(int pipes[][2], int n_cmds);
int			ft_count_cmds(t_data *cmd);
char		*ft_check_built_redir(t_data *data);
t_built		*ft_fill_struct(char **env);
t_built		*ft_update_exp(t_built *line, int flag_cd);
t_built		*ft_sort_vars(t_built *head);
int			ft_specify_var(char *str);
int			ft_is_builtins_f(t_data *data, t_built *line_env, t_exec in);
char		*ft_check_built_redir_f(t_data *data);
char		**ft_fill_envp(t_built *line_env);
t_built		*ft_no_full_env(t_built *line_env);
void		ft_only_print(t_built *line, int flag_one_pth);
void		ft_child_redir(t_data *curr, t_built *line_env,
				t_ex_othr env_here, t_exec in);
char		*ft_check_built_cmd(t_data *data);
void		ft_clean_env(t_built **line_env_ptr);
int			ft_empty_env(char **env);
int			ft_check_this_var(char *str, t_built *line_env);
char		*expanding_heredoc(char *s, t_built *env, t_exec *in);
int			ft_fd_redirections(t_data *data, t_redir *redir);
t_built		*ft_handle_cd(t_data *data, t_built *line_env,
				int *flag_cd, t_exec *in);
void		ft_child_pro_f(t_data *curr, t_built *line_env,
				t_ex_othr env_here, t_exec in);
int			is_only_spaces(char *cmd);
void		ft_check_hered(t_redir *redir);
int			ft_check(char **str, int *i);
int			ft_signle_wait(int status, pid_t last_pid, t_exec *in);
t_data		*ft_get_last_cmd(t_data *tmp, t_exec in);
int			ft_is_interactive_cmd(t_data *tmp);
void		ft_handle_sigint(int flag_interactive, int *signal_printed);
int			ft_multiple_wait(t_data *tmp, t_exec *in,
				int status, pid_t last_pid);
char		*ft_parent_dir(char *current_path);
t_built		*ft_cd_parent(char **str, t_built *line_env,
				int *flag_cd, t_exec *in);
t_built		*ft_cd_normal(char **str, t_built *line_env,
				int *flag_cd, t_exec *in);
t_built		*ft_cd_parent_helper(t_built *line_env, char *curr_pwd,
				int *flag_cd, t_exec *in);
int			ft_is_numeric(const char *str);
int			ft_check_otp_redir(t_redir *redir);
int			ft_have_input_redir(t_data *data);
int			ft_have_output_redir(t_data *data);
int			ft_have_heredoc(t_data *data);
void		ft_check_path_var(t_data *data, t_built *line_env,
				int *flag_one_pth);
int			ft_open_redir(t_redir *redir, int found_hered,
				int *last_input, int *last_output);
char		**ft_have_slash(char **cmd_args);
char		**ft_get_path_f(char *cmd);
int			ft_exec_cmd_1(t_data **data, t_built *line_env,
				t_ex_othr env_here, t_exec *in);
int			ft_in_pp(t_exec *in, t_data *data);
pid_t		ft_fork_and_child(t_data *data, t_built *line_env,
				t_ex_othr env_here, t_exec in);
int			ft_type_0(t_data **data, t_built *line_env,
				t_ex_othr env_here, t_exec *in);
int			ft_no_env_type_0(t_data **data, t_built *line_env,
				t_ex_othr env_here, t_exec *in);
pid_t		ft_no_env_fork_child(t_data *data, t_built *line_env,
				t_ex_othr env_here, t_exec in);
int			ft_init_no_env(t_exec *in, t_ex_othr *env_here,
				t_built *line_env, t_exec stat);
int			ft_init_normal_setup(t_exec *in, t_data *data, t_exec stat);
pid_t		ft_normal_fork_child(t_data *data, t_built *line_env,
				t_ex_othr env_here, t_exec in);
int			ft_normal_type_0(t_data **data, t_built *line_env,
				t_ex_othr env_here, t_exec *in);
void		ft_kill_p(t_pid_list *head);
t_pid_list	*ft_add_pid(t_pid_list *head, pid_t pid);
int			ft_check_no_env(t_built *line_env);
void		ft_creat_pp(t_exec *in);
pid_t		ft_fork_child(t_data *tmp, t_built *line_env,
				t_ex_othr env_here, t_exec *in);
int			ft_open_redir(t_redir *redir, int found_hered,
				int *last_input, int *last_output);
int			ft_open_input_redir_sub(t_redir *redir,
				int found_hered, int *last_input);
int			ft_handle_output_redir(t_redir *curr, int *last_output);

// ******************Libft func******************
char		*ft_strjoin(char *s1, char *s2, int flag_struct);
char		**ft_split(char *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(char *str);
char		*ft_strdup(char *s1, int flag, int struct_flag);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_atoi(const char *str);
void		ft_rm_list(t_built **head, t_built *target);
t_built		*ft_add_front(t_built *head, char *var, char *value);
t_built		*ft_add_back(t_built *line, char *var, char *value);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_substr(char *s, int start, size_t len);
void		*ft_memcpy(void *dst, void *src, size_t n);
void		ft_free_split(char **split);
char		*ft_strnstr(char *haystack, char *needle, int len);
char		*ft_itoa(int n);
void		ft_rm_list_env(t_built **head, t_built *rm_node);
void		ft_close_fd_opening(void);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(char *haystack, char *needle, int len);
int			ft_strstr(const char *haystack, const char *needle);
void		*malloc_cl(size_t size, t_mode mode, int is_static);
int			ft_isdigit(int c);

#endif
