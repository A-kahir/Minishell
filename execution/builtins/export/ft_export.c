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

static int	handle_export_var(t_built *line_env, char *arg, t_exec *in,
	int *valid_var_found)
{
	int	check;

	if (arg[0] == '\0')
		return (0);
	check = ft_specify_var(arg);
	if (check == 4)
		return (0);
	else if (check == 1)
	{
		ft_is_positif(line_env, arg);
		*valid_var_found = 1;
	}
	else if (check == -1)
	{
		write(2, "minishell: export: `", 21);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
		return ((in->status = ft_strdup("1", 0, 0)), -1);
	}
	else if (check == 0)
	{
		ft_add_var(line_env, arg);
		*valid_var_found = 1;
	}
	return (0);
}

t_built	*ft_export(t_built *line_env, char **cmd, int flag_one_pth, t_exec *in)
{
	int	i;
	int	valid_var_found;
	int	flag;

	i = 1;
	valid_var_found = 0;
	flag = 0;
	while (cmd[i])
	{
		flag = handle_export_var(line_env, cmd[i], in, &valid_var_found);
		if (flag == -1 && cmd[i + 1] == NULL)
			return (line_env);
		i++;
	}
	if (!valid_var_found)
		ft_only_print(line_env, flag_one_pth);
	if (!in->status || ft_strcmp(in->status, "1") != 0)
		in->status = ft_strdup("0", 0, 0);
	return (line_env);
}
