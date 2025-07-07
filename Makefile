NAME = minishell

MAND_SRC = \
    mand/utils.c \
    mand/main.c \
    mand/clean.c \
    mand/tokenize.c \
    mand/check.c \
    mand/initializing.c \
    mand/heredoc_position.c \
    mand/expanding.c \

EXEC_SRC = \
	execution/ft_exec.c \
	execution/ft_child_pro.c \
	execution/ft_if_un_path.c \
	execution/ft_no_env.c \
	execution/ft_normal_exec.c \

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
	execution/utils_exec/ft_open_outfile.c \
	execution/utils_exec/ft_child_redir.c \

REDIR_SRC = \
	execution/redirections/ft_tran_app.c \
	execution/redirections/ft_read_f.c \
	execution/redirections/ft_is_redir.c

HEREDOC_SRC = \
	execution/redirections/heredoc/ft_handle_heredoc.c \
	execution/redirections/heredoc/middle/ft_heredoc_middle.c \
	execution/redirections/heredoc/middle/ft_child_hered_middle.c \
	execution/redirections/heredoc/before/ft_heredoc_before.c \
	execution/redirections/heredoc/before/ft_child_hered_before.c \
	execution/redirections/heredoc/after/ft_heredoc_after.c \
	execution/redirections/heredoc/after/ft_child_hered_after.c

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
	execution/libft_func/ft_strncmp.c \
	execution/libft_func/ft_substr.c \
	execution/libft_func/ft_itoa.c 

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

CC = cc -g -fsanitize=address -g #-fsanitize=undefined -g -Wall -Wextra -Werror
RM = rm -f
 CFLAGS = -Wall -Wextra -Werror
# READLINE_INC = -I$(shell brew --prefix readline)/include
# READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

%.o: %.c mand/minishell.h
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lreadline

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
