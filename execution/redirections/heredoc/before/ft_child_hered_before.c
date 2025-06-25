
#include "../../../execution.h"

void	ft_child_hered_bef(t_data *curr, int pipes[][2], int i, int n_cmds, int *hered_fd, char **env)
{
	char	**cmd_args;

	if (hered_fd[i] != -1)
	{
		if (dup2(hered_fd[i], 0) == -1)
			(perror("dup2 input failed"), exit(1));
		close(hered_fd[i]);
	}
	if (i < n_cmds - 1 && dup2(pipes[i][1], 1) == -1)
		(perror("dup2 output failed"), exit(1));
	ft_close_pipes(pipes, n_cmds);
	if (!curr->cmd || !curr->cmd[0])
        exit(0);
	cmd_args = ft_get_path(curr->cmd[0], env);
	if (!cmd_args)
		(printf("minishell: %s: command not found\n", curr->cmd[0]), exit(1));
	if (execve(cmd_args[0], curr->cmd, env) == -1)
		(perror("execve failed"), exit(1));
}
