/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-oua <yael-oua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:41:41 by yael-oua          #+#    #+#             */
/*   Updated: 2025/07/05 18:41:41 by yael-oua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_env_value(const char *var, t_built *env) {
    while (env) {
        if (strcmp(env->var, var) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

static char	*helper_func(char *result, char *s, size_t start, size_t end, t_built *env)
{
    size_t	i;
    char	*tmp;
    char	*var;
    char	*val;
    char	*tmp2;

    tmp = ft_substr_par(s, start, end - start);
    i = end + 1;
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    var = ft_substr_par(s, end + 1, i - (end + 1));
    val = get_env_value(var, env);
    tmp2 = ft_strjoin_par(result, tmp);
    free(result);
    result = tmp2;
    if (val)
    {
        tmp2 = ft_strjoin_par(result, val);
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

char	*expanding(char *s, t_built *env)
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
            result = helper_func(result, s, start, i, env);
            i++;
            while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
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
