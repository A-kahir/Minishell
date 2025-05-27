

#include "execution.h"

void ft_is_builtin(t_data *data, char **env)
{
    if (data->builtin_type == 0)
    {
        ft_echo(data->cmd);
    }
    else if (data->builtin_type == 1)
    {
        ft_cd(data->cmd);
    }
    else if (data->builtin_type == 2)
    {
        ft_pwd(data->cmd);
    }
    else if (data->builtin_type == 3)
    {
        printf("soon code\n");
    }
    else if (data->builtin_type == 4)
    {
        ft_unset(data->cmd, &env);
    }
    else if (data->builtin_type == 5)
    {
        ft_env(data->cmd, env);
    }
    else if (data->builtin_type == 6)
    {
        ft_exit(data->cmd);
    }
}
