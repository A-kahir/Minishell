/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:28:53 by akahir            #+#    #+#             */
/*   Updated: 2025/06/28 20:52:03 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_is_redir(t_data *data, t_built *line_env,
t_ex_othr env_here, t_exec stat)
{
	int	status;
	int	have_heredoc;
	int	have_input;
	int	have_output;

	status = 0;
	have_heredoc = ft_have_heredoc(data);
	have_input = ft_have_input_redir(data);
	have_output = ft_have_output_redir(data);
	if (have_heredoc)
	{
		status = ft_heredoc(data, line_env, env_here, stat);
		return (status);
	}
	if (have_input && !have_heredoc)
		return (ft_read_f(data, line_env, env_here));
	if (have_output)
		return (ft_tran_app(data, line_env, env_here));
	return (0);
}
