/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:27 by akahir            #+#    #+#             */
/*   Updated: 2025/05/22 15:29:22 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum s_type_node
{
	CMD_NODE,
	PIPE_NODE
}	t_type_node;

typedef enum s_type_redir
{
	TRUNCATE,  // >
	APPEND,    // >>
	READ_F,    // <
	HEREDOC    // <<
}	t_type_redir;

typedef struct s_redir
{
	t_type_redir type;
	char *target;
	struct s_redir *next;
}	t_redir;

typedef enum s_type_buil
{
	NOT_BUILTIN = -1,
	IS_ECHO,
	IS_CD,
	IS_PWD,
	IS_EXPORT,
	IS_UNSET,
	IS_ENV,
	IS_EXIT
}	t_type_buil;

typedef struct s_data
{
	t_type_node type;
	t_redir *redir;           // redirection list
	t_type_buil builtin_type; // store the builtin directly (not in a substruct)
	char **cmd;               // {"cd", "Documents", NULL}
	struct s_data *left;
	struct s_data *right;
}	t_data;
#endif