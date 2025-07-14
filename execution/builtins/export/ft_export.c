/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:38 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:09:34 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// int ft_add_vars(char **cmd)
// {
//     int i = 1;
//     int count = 0;

//     while (cmd[i])
//     {
//         if (cmd[i][0] == '$' && ft_strlen(cmd[i]) == 1)
//         {
//             i++;
//             continue;
//         }
//         if (cmd[i][0] == '$' && getenv(cmd[i] + 1) == NULL)
//         {
//             i++;
//             continue;
//         }
//         count++;
//         i++;
//     }
//     return count;
// }


t_built *ft_export(t_built *line_env, char **cmd, int flag_one_pth)
{
	int i = 1;
	int valid_var_found = 0;

	if (ft_strcmp(cmd[0], "export") == 0 && cmd[1] == NULL)
	{
		ft_only_print(line_env, flag_one_pth);
		return (line_env);
	}

	while (cmd[i])
	{
		if (cmd[i][0] == '\0')
		{
			i++;
			continue;
		}

		int check = ft_specify_var(cmd[i]);

		if (check == 4)
		{
			i++;
			continue;
		}
		else if (check == 1)
		{
			ft_is_positif(line_env, cmd[i]);
			valid_var_found = 1;
		}
		else if (check == -1)
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
		}
		else if (check == 0)
		{
			ft_add_var(line_env, cmd[i]);
			valid_var_found = 1;
		}
		i++;
	}
	if (!valid_var_found)
		ft_only_print(line_env, flag_one_pth);

	return line_env;
}
