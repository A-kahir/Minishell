/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:32:17 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 16:32:27 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	match_var(char *env_var, char *to_remove)
{
	int i;

	i = 0;
	while (env_var[i] && env_var[i] != '=' && to_remove[i])
	{
		if (env_var[i] != to_remove[i])
			return (0);
		i++;
	}
	return (to_remove[i] == '\0' && env_var[i] == '=');
}

static void	unset_var(char **args, int *i, char ***env)
{
	char	**n_env;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while ((*env)[j])
		j++;
	n_env = malloc(sizeof(char *) * (j + 1));
	if (!n_env)
		return ;
	j = 0;
	while ((*env)[j])
	{
		if (!match_var((*env)[j], args[*i]))
			n_env[k++] = (*env)[j];
		else
			free((*env)[j]);
		j++;
	}
	n_env[k] = NULL;
	free(*env);
	*env = n_env;
}

static int	is_valid_identifier(char *str)
{
	int i;

	i = 0;
	if (!str || !((str[0] >= 'A' && str[0] <= 'Z') ||
		(str[0] >= 'a' && str[0] <= 'z') || str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char **args, char ***env)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
		else
			unset_var(args, &i, env);
		i++;
	}
}
