#include "execution.h"


t_type_buil check_builtin(char *cmd)
{
	if (strcmp(cmd, "echo") == 0) return IS_ECHO;
	if (strcmp(cmd, "cd") == 0) return IS_CD;
	if (strcmp(cmd, "pwd") == 0) return IS_PWD;
	if (strcmp(cmd, "export") == 0) return IS_EXPORT;
	if (strcmp(cmd, "unset") == 0) return IS_UNSET;
	if (strcmp(cmd, "env") == 0) return IS_ENV;
	if (strcmp(cmd, "exit") == 0) return IS_EXIT;
	return NOT_BUILTIN;
}

char **split_by_space(char *str)
{
	char **result = NULL;
	char *token;
	int i = 0;

	// First pass: count words
	char *tmp = strdup(str);
	char *save = tmp;
	int count = 0;
	token = strtok(tmp, " \t");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(save);

	// Allocate array
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return NULL;

	// Second pass: fill array
	tmp = strdup(str);
	save = tmp;
	token = strtok(tmp, " \t");
	while (token)
	{
		result[i++] = strdup(token);
		token = strtok(NULL, " \t");
	}
	result[i] = NULL;
	free(save);
	return result;
}

int is_empty(char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return 0;
		s++;
	}
	return 1;
}
t_type_redir get_redir_type(char *s)
{
	if (strcmp(s, ">") == 0)
		return TRUNCATE;
	else if (strcmp(s, ">>") == 0)
		return APPEND;
	else if (strcmp(s, "<") == 0)
		return READ_F;
	else if (strcmp(s, "<<") == 0)
		return HEREDOC;
	return NOT_REDIR;
}

t_redir *add_redir(t_redir *head, t_type_redir type, char *target)
{
	t_redir *new = malloc(sizeof(t_redir));
	if (!new) return head;
	new->type = type;
	new->target = strdup(target);
	new->next = NULL;
	if (!head)
		return new;
	t_redir *tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return head;
}

int cmd_array_len(char **cmd) {
    int i = 0;
    while (cmd && cmd[i])
        i++;
    return i;
}

t_data *create_cmd_node(char *cmd_str)
{
	if (!cmd_str || is_empty(cmd_str))
		return NULL;

	t_data *node = malloc(sizeof(t_data));
	if (!node)
		return NULL;

	node->type = CMD_NODE;
	node->redir = NULL;
	node->builtin_type = NOT_BUILTIN;
	node->left = NULL;
	node->right = NULL;

	char **tokens = split_by_space(cmd_str);
	int i = 0;
	char **cmd_parts = malloc(sizeof(char *) * (cmd_array_len(tokens) + 1));
	int j = 0;

	while (tokens[i])
	{
		t_type_redir redir_type = NOT_REDIR;

		if ((redir_type = get_redir_type(tokens[i])) != NOT_REDIR)
		{
			if (tokens[i + 1])
			{
				node->redir = add_redir(node->redir, redir_type, tokens[i + 1]);
				i += 2;
				continue;
			}
			else
				break; // Invalid syntax, skip
		}
		cmd_parts[j++] = strdup(tokens[i++]);
	}
	cmd_parts[j] = NULL;

	for (int k = 0; tokens[k]; k++)
		free(tokens[k]);
	free(tokens);

	node->cmd = cmd_parts;
	if (node->cmd && node->cmd[0])
		node->builtin_type = check_builtin(node->cmd[0]);

	return node;
}


int count_pipes(char *input)
{
	int count = 0;
	for (int i = 0; input[i]; i++)
		if (input[i] == '|')
			count++;
	return count;
}

char **split_by_pipe(char *input, int *count)
{
	int pipes = count_pipes(input);
	*count = pipes + 1;

	char **tokens = malloc(sizeof(char *) * (*count));
	char *input_dup = strdup(input);
	char *saveptr = NULL;

	char *token = strtok_r(input_dup, "|", &saveptr);
	int i = 0;
	while (token && i < *count)
	{
		while (*token == ' ' || *token == '\t') token++;
		int len = strlen(token);
		while (len > 0 && (token[len-1] == ' ' || token[len-1] == '\t')) token[--len] = '\0';

		tokens[i++] = strdup(token);
		token = strtok_r(NULL, "|", &saveptr);
	}
	free(input_dup);
	return tokens;
}

// Helper to merge two cmd arrays into a new one
char **merge_cmd_arrays(char **a, char **b) {
    int len_a = cmd_array_len(a);
    int len_b = cmd_array_len(b);
    char **merged = malloc(sizeof(char *) * (len_a + len_b + 1));
    if (!merged) return NULL;

    for (int i = 0; i < len_a; i++)
        merged[i] = strdup(a[i]);
    for (int j = 0; j < len_b; j++)
        merged[len_a + j] = strdup(b[j]);

    merged[len_a + len_b] = NULL;
    return merged;
}

t_data *build_tree_from_pipes(char **tokens, int start, int end) {
    if (start > end)
        return NULL;

    t_data *left = create_cmd_node(tokens[start]);
    if (!left) return NULL;

    for (int i = start + 1; i <= end; i++) {
        t_data *pipe_node = malloc(sizeof(t_data));
        if (!pipe_node)
            return NULL;
        pipe_node->type = PIPE_NODE;
        pipe_node->redir = NULL;
        pipe_node->builtin_type = NOT_BUILTIN;
        pipe_node->left = left;

        t_data *right_cmd = create_cmd_node(tokens[i]);
        pipe_node->right = right_cmd;

        // Merge cmd arrays from left node and right command node
        pipe_node->cmd = merge_cmd_arrays(left->cmd, right_cmd->cmd);

        // free left->cmd and right_cmd->cmd because merged cmd is duplicated strings
        for (int k = 0; left->cmd && left->cmd[k]; k++)
            free(left->cmd[k]);
        free(left->cmd);
        left->cmd = NULL;

        for (int k = 0; right_cmd->cmd && right_cmd->cmd[k]; k++)
            free(right_cmd->cmd[k]);
        free(right_cmd->cmd);
        right_cmd->cmd = NULL;

        left = pipe_node;
    }
    return left;
}

void free_tree(t_data *root)
{
	if (!root)
		return;

	if (root->cmd)
	{
		for (int i = 0; root->cmd[i]; i++)
			free(root->cmd[i]);
		free(root->cmd);
	}
	if (root->redir)
	{
		t_redir *r = root->redir;
		while (r)
		{
			t_redir *tmp = r;
			free(r->target);
			r = r->next;
			free(tmp);
		}
	}
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

// ------------ Main Function ------------

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    while (1)
    {
        char *input = readline("Minishell-3.2$~ ");
        if (!input)
            break;
        if (strlen(input) == 0)
        {
            free(input);
            continue;
        }
        add_history(input);
        int pipe_count = 0;
        char **pipe_tokens = split_by_pipe(input, &pipe_count);
        if (!pipe_tokens)
        {
            free(input);
            continue;
        }

        // Build the tree properly from pipe tokens
        t_data *root = build_tree_from_pipes(pipe_tokens, 0, pipe_count - 1);
        if (!root)
        {
            for (int i = 0; i < pipe_count; i++)
                free(pipe_tokens[i]);
            free(pipe_tokens);
            free(input);
            continue;
        }

        ft_exec(root, env);

        for (int i = 0; i < pipe_count; i++)
            free(pipe_tokens[i]);
        free(pipe_tokens);

        free_tree(root);
        free(input);
    }
    return 0;
}

