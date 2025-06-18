#include "../../execution.h"

static t_built *create_and_insert_node(t_built *line, char **cmd, t_built *prev, t_built *current)
{
    t_built *new_node = malloc(sizeof(t_built));
    if (!new_node)
        return line;
    new_node->var = strdup(cmd[1]);
    new_node->value = strdup(cmd[2]);
    if (!new_node->var || !new_node->value)
    {
        free(new_node->var);
        free(new_node->value);
        free(new_node);
        return line;
    }
    new_node->next = current;
    if (prev)
        prev->next = new_node;
    else
        line = new_node;
    return line;
}

t_built *ft_sort_by_order(t_built *line, char **cmd)
{
    t_built *prev = NULL;
    t_built *current = line;
    while (current)
    {
        if (ft_strcmp(cmd[1], current->var) == 0)
        {
            free(current->value);
            current->value = strdup(cmd[2]);
            if (!current->value)
                return line;
            return line;
        }
        if (ft_strcmp(cmd[1], current->var) < 0)
            break;
        prev = current;
        current = current->next;
    }
    return create_and_insert_node(line, cmd, prev, current);
}
