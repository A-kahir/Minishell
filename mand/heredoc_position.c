/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:57:59 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/22 14:52:29 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*helper_func(char *result, char *s, int start, int end, t_built *env, t_exec *in)
{
    int	i;
    char	*tmp;
    char	*var;
    char	*val;
    char	*tmp2;

    tmp = ft_substr_par(s, start, end - start);
    i = end + 1;
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
        i++;
    var = ft_substr_par(s, end + 1, i - (end + 1));
    val = get_env_value(var, env);
    tmp2 = ft_strjoin_par(result, tmp);
    free(result);
    result = tmp2;
    if (val && !ft_strchr(val, ' ') && !ft_strchr(val, '\t'))
    {
        tmp2 = ft_strjoin_par(result, val);
        free(result);
        result = tmp2;
    }
    else if (!ft_strcmp(var, "?"))
    {
        tmp2 = ft_strjoin_par(result, in->status);
        free(result);
        result = tmp2;
    }
    else if(!ft_strcmp(var, "_") && in->last_cmd && !ft_strchr(in->last_cmd, ' ') && !ft_strchr(in->last_cmd, '\t'))
    {
        tmp2 = ft_strjoin_par(result, in->last_cmd);
        free(result);
        result = tmp2;
    }
    else
    {
        tmp2 = ft_strjoin_par(result, ft_strjoin_par("$", var));
        free(result);
        result = tmp2;
    }
    free(tmp);
    free(var);
    return (result);
}

char	*expanding_target(char *s, t_built *env, t_exec *in)
{
    int	i;
    int	start;
    char	*result;
    char	*tail;
    char	*tmp;

    1 && (i = 0, start = 0, result = ft_strdup(""));
    if (!result)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '$')
        {
            result = helper_func(result, s, start, i, env, in);
            i++;
            while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
                i++;
            start = i;
        }
        else
            i++;
    }
    if (start < i)
    {
        tail = ft_substr_par(s, start, i - start);
        tmp = ft_strjoin_par(result, tail);
        free(result);
        result = tmp;
        free(tail);
    }
    return (result);
}
