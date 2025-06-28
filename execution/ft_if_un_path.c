
#include "execution.h"

void ft_if_un_path(t_data *data, t_ex_othr env_here, t_built *line_env)
{
	t_exec	in;
	int		flag_redir;
	char *command;

	flag_redir = ft_flag_redir(data);
	command = ft_check_built_redir(data);
	if ((ft_strcmp(command, "cmd") == 0 && flag_redir == 0) || data->builtin_type == 5)
		printf("minishell: %s: No such file or directory\n", data->cmd[0]);
	if (ft_strcmp(command, "built") == 0 && data->builtin_type != -1 && data->builtin_type != 5)
		ft_is_builtins_f(data, line_env);
	if (ft_flag_redir(data) == 1)
		ft_is_redir(data, env_here.env, env_here.heredoc);
}
