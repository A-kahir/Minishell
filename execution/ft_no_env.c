
#include "execution.h"

void ft_no_env(t_data *data, t_ex_othr env_here, t_built *line_env)
{
	pid_t	pid;
	t_exec	in;
	int		flag_redir;
	char *command;

	ft_no_full_env(line_env);
	env_here.env = ft_fill_envp(line_env);
	command = ft_check_built_redir(data);
	flag_redir = ft_flag_redir(data);
	in.n_cmds = ft_count_cmds(data);
	in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
	if (!in.pipes)
		return ;
	int i = 0;
	while (i < in.n_cmds - 1)
		if (pipe(in.pipes[i++]) == -1)
			(perror("Pipe creation failed"), exit(1));
	if (ft_strcmp(command, "cmd") == 0 && flag_redir == 0)
	{
		in.i = 0;
		while (in.i < in.n_cmds)
		{
			pid = fork();
			if (pid == -1)
				(ft_close_pipes(in.pipes, in.n_cmds), perror("Fork failed"), exit(1));
			else if (pid == 0)
				ft_child_pro(data, line_env, env_here, in);
			data = data->next;
			in.i++;
		}
		ft_close_pipes(in.pipes, in.n_cmds);
		while (wait(NULL) > 0);
		free(in.pipes);
	}
	if (ft_strcmp(command, "built") == 0 && flag_redir == 0)
		ft_is_builtins(data, line_env);
	if (flag_redir == 1)
		ft_is_redir(data, env_here.env, env_here.heredoc);
}
