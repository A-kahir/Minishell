NAME = minishell

MAND_SRC = \
    mand/utils.c \
	mand/clean.c \
    mand/main.c \
    mand/tokenize_helpers.c \
    mand/tokenize_func.c \
    mand/check.c \
    mand/check2.c \
    mand/initializing.c \
    mand/initializing2.c \
    mand/expanding_target.c \
    mand/expanding.c \
    mand/heredo_expanding.c \
    mand/retokenize.c \
    mand/retokenize_helpers.c \
    mand/token_target.c \
    mand/utils2.c \
	mand/redir_command.c \
	mand/parsing.c \

EXEC_SRC = \
	execution/ft_exec.c \
	execution/ft_child_pro.c \
	execution/ft_if_un_path.c \
	execution/ft_no_env.c \
	execution/ft_normal_exec.c \
	execution/ft_child_pro_f.c \

UTILS_EXEC_SRC = \
	execution/utils_exec/ft_update_exp.c \
	execution/utils_exec/ft_sort_vars.c \
	execution/utils_exec/ft_free_split.c \
	execution/utils_exec/ft_flag_redir.c \
	execution/utils_exec/ft_fill_struct.c \
	execution/utils_exec/ft_count_cmd.c \
	execution/utils_exec/ft_close_pipes.c \
	execution/utils_exec/ft_check_built_redir.c \
	execution/utils_exec/ft_check_built_redir_f.c \
	execution/utils_exec/ft_is_positif.c \
	execution/utils_exec/ft_specify_var.c \
	execution/utils_exec/ft_builtins_f.c \
	execution/utils_exec/ft_fill_envp.c \
	execution/utils_exec/ft_get_path.c \
	execution/utils_exec/ft_no_full_env.c \
	execution/utils_exec/ft_only_print.c \
	execution/utils_exec/ft_child_redir.c \
	execution/utils_exec/ft_clean_env.c \
	execution/utils_exec/ft_empty_env.c \
	execution/utils_exec/ft_check_this_var.c \
	execution/utils_exec/ft_fd_redirection.c \
	execution/utils_exec/ft_check_for_echo.c \
	execution/utils_exec/ft_check_hered.c \
	execution/utils_exec/ft_signle_wait.c \
	execution/utils_exec/ft_multiple_wait.c \
	execution/utils_exec/ft_parent_dir.c \
	execution/utils_exec/ft_cd_normal.c \
	execution/utils_exec/ft_cd_parent.c \
	execution/utils_exec/ft_is_numiric.c \
	execution/utils_exec/ft_specify_type_redir.c \
	execution/utils_exec/ft_child_read_f.c \
	execution/utils_exec/ft_check_path_var.c \
	execution/utils_exec/ft_open_redirections_fd.c \
	execution/utils_exec/ft_only_spaces.c \
	execution/utils_exec/ft_errno_print.c \
	execution/utils_exec/ft_get_path_f.c \
	execution/utils_exec/cantinue_un_path.c \
	execution/utils_exec/cantinue_no_env.c \
	execution/utils_exec/count_normal.c \
	execution/utils_exec/ft_open_red.c \
	execution/utils_exec/cantinue_mul_wait.c \
	execution/utils_exec/ft_kill_pids.c \
	execution/utils_exec/ft_add_pid.c \
	execution/utils_exec/ft_cant_trunc_app_help.c \

REDIR_SRC = \
	execution/redirections/ft_tran_app.c \
	execution/redirections/ft_read_f.c \
	execution/redirections/ft_is_redir.c \

HEREDOC_SRC = \
	execution/redirections/heredoc/ft_handle_heredoc.c \
	execution/redirections/heredoc/ft_heredoc.c \
	execution/redirections/heredoc/ft_child_heredoc.c

LIBFT_FUNC_SRC = \
	execution/libft_func/ft_add_back.c \
	execution/libft_func/ft_add_front.c \
	execution/libft_func/ft_atoi.c \
	execution/libft_func/ft_rm_list.c \
	execution/libft_func/ft_split.c \
	execution/libft_func/ft_strchr.c \
	execution/libft_func/ft_is_digit.c \
	execution/libft_func/ft_memcpy.c \
	execution/libft_func/ft_strcmp.c \
	execution/libft_func/ft_strdup.c \
	execution/libft_func/ft_strjoin.c \
	execution/libft_func/ft_strlen.c \
	execution/libft_func/ft_memset.c \
	execution/libft_func/ft_strncmp.c \
	execution/libft_func/ft_substr.c \
	execution/libft_func/ft_itoa.c \
	execution/libft_func/ft_rm_list_env.c \
	execution/libft_func/ft_close_fd_opening.c \
	execution/libft_func/ft_strrchr.c \
	execution/libft_func/ft_strstr.c \
	execution/libft_func/malloc_cl.c \
	execution/libft_func/ft_strnstr.c \

BUILTINS_SRC = \
	execution/builtins/ft_unset.c \
	execution/builtins/ft_pwd.c \
	execution/builtins/ft_is_builtins.c \
	execution/builtins/ft_exit.c \
	execution/builtins/ft_env.c \
	execution/builtins/ft_echo.c \
	execution/builtins/ft_cd.c \
	execution/builtins/export/ft_add_var.c \
	execution/builtins/export/ft_export.c

SRC = $(MAND_SRC) $(EXEC_SRC) $(UTILS_EXEC_SRC) $(REDIR_SRC) $(HEREDOC_SRC) $(LIBFT_FUNC_SRC) $(BUILTINS_SRC)

OBJS = $(SRC:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline 

%.o: %.c mand/minishell.h execution/execution.h
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(READLINE_LIB)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean