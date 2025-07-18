#include "../execution.h"

int ft_handle_mixed_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    t_data *curr;
    t_exec in;
    int status;

    in.n_cmds = ft_count_cmds(data);
    if (in.n_cmds == 0)
        return (0);
    
    if (in.n_cmds > 1)
    {
        in.pipes = malloc(sizeof(int[2]) * (in.n_cmds - 1));
        if (!in.pipes)
        {
            perror("malloc failed");
            return (1);
        }
        
        in.i = 0;
        while (in.i < in.n_cmds - 1)
        {
            if (pipe(in.pipes[in.i]) == -1)
            {
                ft_close_pipes(in.pipes, in.i);
                free(in.pipes);
                perror("pipe creation failed");
                return (1);
            }
            in.i++;
        }
    }
    
    curr = data;
    in.i = 0;
    while (in.i < in.n_cmds)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            if (in.n_cmds > 1)
            {
                ft_close_pipes(in.pipes, in.n_cmds - 1);
                free(in.pipes);
            }
            perror("fork failed");
            return (1);
        }
        else if (pid == 0)
            ft_child_redir(curr, line_env, env_here, in);
        
        curr = curr->next;
        in.i++;
    }
    
    if (in.n_cmds > 1)
    {
        ft_close_pipes(in.pipes, in.n_cmds - 1);
        free(in.pipes);
    }
    
    while (wait(&status) > 0)
        ;
    
    return (WEXITSTATUS(status));
}


int ft_execute_with_redir(t_data *data, t_built *line_env, t_ex_othr env_here, t_exec stat)
{
    if (ft_has_input_redir(data) && !ft_has_output_redir(data))
        return ft_read_f(data, line_env, env_here);
    else if (ft_has_output_redir(data) && !ft_has_input_redir(data))
        return ft_tran_app(data, line_env, env_here, stat);
    else if (ft_has_input_redir(data) && ft_has_output_redir(data))
        return ft_handle_mixed_redir(data, line_env, env_here, stat);
    
    return (0);
}
