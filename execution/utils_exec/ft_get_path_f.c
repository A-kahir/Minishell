/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:51:54 by akahir            #+#    #+#             */
/*   Updated: 2025/07/29 12:10:36 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	ft_print_error_and_exit_f(char *cmd, int errno_typ)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	if (errno_typ == 1)
		write(2, ": is a directory\n", 18);
	else if (errno_typ == 2)
		write(2, ": Not a directory\n", 19);
	else if (errno_typ == 3)
		write(2, ": No such file or directory\n", 29);
	else if (errno_typ == 4)
		write(2, ": Permission denied\n", 21);
	if (errno_typ == 3)
		exit(127);
	else
		exit(126);
}

char	**ft_have_slash_f(char **cmd_args)
{
	struct stat	data;

	errno = 0;
	if (access(cmd_args[0], X_OK) == 0)
	{
		if (stat(cmd_args[0], &data) == 0 && S_ISDIR(data.st_mode))
			ft_print_error_and_exit_f(cmd_args[0], 1);
		return (cmd_args);
	}
	else
	{
		if (errno == ENOTDIR)
			ft_print_error_and_exit_f(cmd_args[0], 2);
		else if (errno == ENOENT)
			ft_print_error_and_exit_f(cmd_args[0], 3);
		else
			ft_print_error_and_exit_f(cmd_args[0], 4);
		return (NULL);
	}
}

char	**ft_get_path_f(char *cmd)
{
	char	**cmd_args;

	if (is_only_spaces(cmd))
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (cmd_args[1])
		return (NULL);
	if (!cmd_args || !cmd_args[0])
		return (NULL);
	if (access(cmd_args[0], X_OK) == 0 && !ft_strchr(cmd_args[0], '/')
		&& !ft_isdigit(cmd[0]))
	{
		return (cmd_args);
	}
	if (ft_strchr(cmd_args[0], '/'))
		return (ft_have_slash_f(cmd_args));
	return (NULL);
}
