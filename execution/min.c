#include "execution.h"

// Function to check if a command is a built-in
t_type_buil check_builtin(char *cmd)
{
    if (!cmd || !*cmd) return (NOT_BUILTIN);
    if (!strcmp(cmd, "echo")) return (IS_ECHO);
    if (!strcmp(cmd, "cd")) return (IS_CD);
    if (!strcmp(cmd, "pwd")) return (IS_PWD);
    if (!strcmp(cmd, "export")) return (IS_EXPORT);
    if (!strcmp(cmd, "unset")) return (IS_UNSET);
    if (!strcmp(cmd, "env")) return (IS_ENV);
    if (!strcmp(cmd, "exit")) return (IS_EXIT);
    return (NOT_BUILTIN);
}

// Function to check if a token is a redirection
t_type_redir check_redirection(char *token)
{
    if (!token || !*token) return (NOT_REDIR);
    if (!strcmp(token, ">")) return (TRUNCATE);
    if (!strcmp(token, ">>")) return (APPEND);
    if (!strcmp(token, "<")) return (READ_F);
    if (!strcmp(token, "<<")) return (HEREDOC);
    return (NOT_REDIR);
}

// Function to create a redirection node
t_redir *create_redir_node(t_type_redir type, char *target)
{
    t_redir *new = malloc(sizeof(t_redir));
    if (!new || !target) return (NULL);
    new->type = type;
    new->target = strdup(target);
    if (!new->target) return (free(new), NULL);
    new->next = NULL;
    return (new);
}

// Function to add a redirection node to the list
void add_redir_to_list(t_redir **list, t_redir *new_redir)
{
    t_redir *cur = *list;
    if (!cur) { *list = new_redir; return; }
    while (cur->next) cur = cur->next;
    cur->next = new_redir;
}

// Function to create a data node
t_data *create_data_node(void)
{
    t_data *node = malloc(sizeof(t_data));
    if (!node) return (NULL);
    node->type = CMD_NODE;
    node->redir = NULL;
    node->builtin_type = NOT_BUILTIN;
    node->cmd = NULL;
    node->next = NULL;
    return (node);
}

// Function to tokenize input, splitting var=value for export
char **tokenize_input(char *input)
{
    int cap = 64, i = 0;
    char **tokens = malloc(sizeof(char*) * cap);
    if (!tokens)
        return NULL;

    char *cpy = strdup(input);
    if (!cpy)
        return NULL;

    char *tok = strtok(cpy, " \t\n");
    while (tok)
    {
        if (i >= cap - 1)
        {
            cap *= 2;
            tokens = realloc(tokens, sizeof(char*) * cap);
            if (!tokens)
            {
                free(cpy);
                return NULL;
            }
        }
        tokens[i++] = strdup(tok);
        tok = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;

    // No special processing needed - keep var=value intact
    
    free(cpy);
    return tokens;
}

// Function to count command arguments, skipping redirections
int count_cmd_args(char **tokens, int start, int end)
{
    int count = 0;
    for (int i = start; i < end; i++)
    {
        if (check_redirection(tokens[i]) != NOT_REDIR)
            i++;
        else
            count++;
    }
    return count;
}

// Updated function to extract command arguments without merging export args
char **extract_cmd_args(char **tokens, int start, int end)
{
    int count = count_cmd_args(tokens, start, end);
    char **args = malloc(sizeof(char*) * (count + 1));
    if (!args)
        return NULL;
    int i = start, j = 0;

    while (i < end)
    {
        if (check_redirection(tokens[i]) != NOT_REDIR)
            i += 2; // Skip redirection token and its target
        else
            args[j++] = strdup(tokens[i++]);
    }
    args[j] = NULL;
    return args;
}

// Function to extract redirections
t_redir *extract_redirections(char **tokens, int start, int end)
{
    t_redir *list = NULL;
    for (int i = start; i < end; i++)
    {
        t_type_redir type = check_redirection(tokens[i]);
        if (type != NOT_REDIR && i + 1 < end)
            add_redir_to_list(&list, create_redir_node(type, tokens[++i]));
    }
    return list;
}

// Function to parse input into t_data nodes
t_data *parse_input(char *input)
{
    char **tokens = tokenize_input(input);
    t_data *head = NULL, *cur = NULL;
    int start = 0, i = 0;

    while (tokens[i])
    {
        if (!strcmp(tokens[i], "|"))
        {
            t_data *node = create_data_node();
            node->cmd = extract_cmd_args(tokens, start, i);
            node->builtin_type = (node->cmd) ? check_builtin(node->cmd[0]) : NOT_BUILTIN;
            node->redir = extract_redirections(tokens, start, i);
            node->type = PIPE_NODE;
            if (!head)
                head = node;
            else
                cur->next = node;
            cur = node;
            start = i + 1;
        }
        i++;
    }
    if (start < i)
    {
        t_data *node = create_data_node();
        node->cmd = extract_cmd_args(tokens, start, i);
        node->builtin_type = (node->cmd) ? check_builtin(node->cmd[0]) : NOT_BUILTIN;
        node->redir = extract_redirections(tokens, start, i);
        node->type = CMD_NODE;
        if (!head)
            head = node;
        else
            cur->next = node;
    }
    for (i = 0; tokens[i]; free(tokens[i++]));
    free(tokens);
    return head;
}

// Function to free the data structure
void free_data_structure(t_data *data)
{
    while (data)
    {
        t_data *next = data->next;
        for (int i = 0; data->cmd && data->cmd[i]; free(data->cmd[i++]));
        free(data->cmd);
        t_redir *r = data->redir;
        while (r) { t_redir *n = r->next; free(r->target); free(r); r = n; }
        free(data);
        data = next;
    }
}

// Function to detect heredoc position
void detect_heredoc_position(t_data *data, t_heredoc *heredoc, char *original_input)
{
    t_data *cur = data;
    int i = 0, pos = -1, has_before = 0, has_after = 0;

    heredoc->before_hered = heredoc->middle_hered = heredoc->after_hered = 0;
    while (cur)
    {
        t_redir *r = cur->redir;
        while (r && r->type != HEREDOC) r = r->next;
        if (r) { pos = i; break; }
        cur = cur->next; i++;
    }
    if (pos == -1) return;

    cur = data;
    for (int j = 0; j < pos; j++, cur = cur->next)
        if (cur->cmd && cur->cmd[0]) has_before = 1;
    for (int j = 0; j <= pos; j++, cur = cur->next);
    while (cur)
    {
        if (cur->cmd && cur->cmd[0]) has_after = 1;
        cur = cur->next;
    }
    if (i == 1) heredoc->before_hered = 1;
    else if (has_before && has_after) heredoc->middle_hered = 1;
    else if (has_before) heredoc->before_hered = 1;
    else if (has_after) heredoc->after_hered = 1;
    else heredoc->before_hered = 1;
}

// Function to merge commands for middle heredoc
void merge_middle_heredoc_cmd(t_data *data)
{
    t_data *cur = data;
    while (cur && cur->next)
    {
        t_redir *r = cur->redir;
        while (r)
        {
            if (r->type == HEREDOC && cur->next && cur->next->cmd)
            {
                int len1 = 0, len2 = 0, i = 0;
                while (cur->cmd && cur->cmd[len1]) len1++;
                while (cur->next->cmd && cur->next->cmd[len2]) len2++;
                char **new = malloc(sizeof(char*) * (len1 + len2 + 1));
                for (; i < len1; i++) new[i] = cur->cmd[i];
                for (int j = 0; j < len2; j++, i++) new[i] = cur->next->cmd[j];
                new[i] = NULL;
                free(cur->cmd); free(cur->next->cmd);
                cur->cmd = new; cur->next->cmd = NULL;
                return;
            }
            r = r->next;
        }
        cur = cur->next;
    }
}

#include "execution.h"

// ... your other functions here ...

void replace_export_dollar_vars(t_data *data, t_built *env)
{
    while (data)
    {
        if (data->cmd && data->cmd[0] && ft_strcmp(data->cmd[0], "export") == 0)
        {
            for (int i = 1; data->cmd[i]; i++)
            {
                char *arg = data->cmd[i];
                if (arg && arg[0] == '$')
                {
                    char *equal_sign = ft_strchr(arg, '=');
                    if (equal_sign)
                    {
                        int var_len = equal_sign - (arg + 1);
                        char *var_name = ft_substr(arg + 1, 0, var_len);
                        if (!var_name)
                        {
                            i++;
                            continue;
                        }
                        char *rest_value = strdup(equal_sign);
                        if (!rest_value)
                        {
                            free(var_name);
                            i++;
                            continue;
                        }

                        t_built *cur = env;
                        int found = 0;
                        while (cur)
                        {
                            if (cur->var && ft_strcmp(cur->var, var_name) == 0)
                            {
                                found = 1;
                                if (cur->value && cur->value[0] != '\0')
                                {
                                    char *new_str = ft_strjoin(cur->value, rest_value);
                                    if (new_str)
                                    {
                                        free(data->cmd[i]);
                                        data->cmd[i] = new_str;
                                    }
                                }
                                break;
                            }
                            cur = cur->next;
                        }
                        free(var_name);
                        free(rest_value);
                    }
                    else
                    {
                        char *var_name = arg + 1;
                        t_built *cur = env;
                        int found = 0;
                        while (cur)
                        {
                            if (cur->var && ft_strcmp(cur->var, var_name) == 0)
                            {
                                found = 1;
                                if (cur->value && cur->value[0] != '\0')
                                {
                                    char *dup_val = strdup(cur->value);
                                    if (dup_val)
                                    {
                                        free(data->cmd[i]);
                                        data->cmd[i] = dup_val;
                                    }
                                }
                                break;
                            }
                            cur = cur->next;
                        }
                    }
                }
            }
        }
        data = data->next;
    }
}

int main(int ac, char **av, char **envp)
{
    char *input;
    t_data *parsed;
    t_heredoc *heredoc;
    static t_built *line_env;

    line_env = ft_fill_struct(envp);

    while ((input = readline("minishell-3.2$~ ")))
    {
        if (*input)
            add_history(input);
        parsed = parse_input(input);
        if (parsed)
        {
            heredoc = malloc(sizeof(t_heredoc));
            detect_heredoc_position(parsed, heredoc, input);
            if (heredoc->middle_hered)
                merge_middle_heredoc_cmd(parsed);

            replace_export_dollar_vars(parsed, line_env);

            ft_exec(parsed, envp, heredoc, line_env);

            free(heredoc);
            free_data_structure(parsed);
        }
        free(input);
    }
    return 0;
}
