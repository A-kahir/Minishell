/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:25:55 by akahir            #+#    #+#             */
/*   Updated: 2025/07/24 18:26:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_parent_dir(char *current_path)
{
	char	*parent_pth;
	char	*last_slash;
	int		len;

	if (!current_path || ft_strcmp(current_path, "/") == 0)
		return (ft_strdup("/", 0, 1));
	len = ft_strlen(current_path);
	parent_pth = ft_strdup(current_path, 0, 1);
	if (len > 1 && parent_pth[len - 1] == '/')
		parent_pth[len - 1] = '\0';
	last_slash = ft_strrchr(parent_pth, '/');
	if (last_slash)
	{
		if (last_slash == parent_pth)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
	}
	else
	{
		return (ft_strdup("/", 0, 1));
	}
	return (parent_pth);
}
