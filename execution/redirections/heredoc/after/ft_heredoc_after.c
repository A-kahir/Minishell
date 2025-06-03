

#include "../../../execution.h"

void ft_heredoc_after(t_data *data, char **env)
{
    int n_cmds = ft_count_cmds(data);
    int *hered_fd = malloc(sizeof(int) * n_cmds);
    if (!hered_fd)
        exit(1);
    t_data *tmp = data;
    int i = 0;
    while (i < n_cmds)
    {
        hered_fd[i] = -1;
        t_redir *redir = tmp->redir;
        while (redir)
        {
            if (redir->type == 3)
            {
                if (hered_fd[i] != -1)
                    close(hered_fd[i]);
                hered_fd[i] = ft_handle_heredoc(redir->target);
            }
            redir = redir->next;
        }
        tmp = tmp->next;
        i++;
    }
    int (*pipes)[2] = malloc(sizeof(int[2]) * (n_cmds - 1));
    if (!pipes)
        exit(1);
    i = 0;
    while (i < n_cmds - 1)
    {
        if (pipe(pipes[i]) == -1)
            (perror("Pipe creation failed"), exit(1));
        i++;
    }
    t_data *curr = data;
    i = 0;
    while (i < n_cmds)
    {
        pid_t pid = fork();
        if (pid == -1)
            perror("Fork failed"), ft_close_pipes(pipes, n_cmds), exit(1);
        else if (pid == 0)
        {
            ft_child_hered_aft(curr, pipes, i, n_cmds, hered_fd, env);
        }
        curr = curr->next;
        i++;
    }
    ft_close_pipes(pipes, n_cmds);
    i = 0;
    while (i < n_cmds)
    {
        if (hered_fd[i] != -1)
            close(hered_fd[i]);
        i++;
    }
    while (wait(NULL) > 0);
    free(pipes);
    free(hered_fd);
}
