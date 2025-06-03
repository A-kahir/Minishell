#include "execution.h"

// Function to check if a string is a builtin command
t_type_buil check_builtin(char *cmd)
{
	if (!cmd || !*cmd)
		return (NOT_BUILTIN);
	if (strcmp(cmd, "echo") == 0)
		return (IS_ECHO);
	if (strcmp(cmd, "cd") == 0)
		return (IS_CD);
	if (strcmp(cmd, "pwd") == 0)
		return (IS_PWD);
	if (strcmp(cmd, "export") == 0)
		return (IS_EXPORT);
	if (strcmp(cmd, "unset") == 0)
		return (IS_UNSET);
	if (strcmp(cmd, "env") == 0)
		return (IS_ENV);
	if (strcmp(cmd, "exit") == 0)
		return (IS_EXIT);
	return (NOT_BUILTIN);
}

// Function to check if a token is a redirection operator
t_type_redir check_redirection(char *token)
{
	if (!token || !*token)
		return (NOT_REDIR);
	if (strcmp(token, ">") == 0)
		return (TRUNCATE);
	if (strcmp(token, ">>") == 0)
		return (APPEND);
	if (strcmp(token, "<") == 0)
		return (READ_F);
	if (strcmp(token, "<<") == 0)
		return (HEREDOC);
	return (NOT_REDIR);
}

// Function to create a new redirection node
t_redir *create_redir_node(t_type_redir type, char *target)
{
	t_redir *new_redir;

	if (!target)
		return (NULL);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->target = strdup(target);
	if (!new_redir->target)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}

// Function to add a redirection to the list
void add_redir_to_list(t_redir **redir_list, t_redir *new_redir)
{
	t_redir *current;

	if (!*redir_list)
	{
		*redir_list = new_redir;
		return;
	}
	current = *redir_list;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

// Function to create a new data node
t_data *create_data_node(void)
{
	t_data *new_data = malloc(sizeof(t_data));
	if (!new_data)
		return (NULL);
	new_data->type = CMD_NODE;
	new_data->redir = NULL;
	new_data->builtin_type = NOT_BUILTIN;
	new_data->cmd = NULL;
	new_data->next = NULL;
	return (new_data);
}

// Function to tokenize input string
char **tokenize_input(char *input)
{
	char **tokens;
	char *token;
	char *input_copy;
	int count = 0;
	int capacity = 64;

	if (!input)
		return (NULL);
	input_copy = strdup(input);
	if (!input_copy)
		return (NULL);
	tokens = malloc(sizeof(char*) * capacity);
	if (!tokens)
	{
		free(input_copy);
		return (NULL);
	}

	token = strtok(input_copy, " \t\n");
	while (token != NULL)
	{
		if (count >= capacity - 1)
		{
			capacity *= 2;
			tokens = realloc(tokens, sizeof(char*) * capacity);
			if (!tokens)
			{
				free(input_copy);
				return (NULL);
			}
		}
		tokens[count] = strdup(token);
		if (!tokens[count])
		{
			free(input_copy);
			return (NULL);
		}
		count++;
		token = strtok(NULL, " \t\n");
	}
	tokens[count] = NULL;
	free(input_copy);
	return (tokens);
}

// Function to count command arguments (excluding redirections)
int count_cmd_args(char **tokens, int start, int end)
{
	int count = 0;
	int i = start;

	while (i < end)
	{
		if (check_redirection(tokens[i]) != NOT_REDIR)
		{
			i += 2; // skip redirection operator and target
			continue;
		}
		count++;
		i++;
	}
	return (count);
}

// Function to extract command arguments
char **extract_cmd_args(char **tokens, int start, int end)
{
	int count = count_cmd_args(tokens, start, end);
	char **cmd_args;
	int i = start;
	int j = 0;

	if (count == 0)
		return (NULL);

	cmd_args = malloc(sizeof(char*) * (count + 1));
	if (!cmd_args)
		return (NULL);

	while (i < end)
	{
		if (check_redirection(tokens[i]) != NOT_REDIR)
		{
			i += 2;
			continue;
		}
		cmd_args[j] = strdup(tokens[i]);
		if (!cmd_args[j])
		{
			while (--j >= 0)
				free(cmd_args[j]);
			free(cmd_args);
			return (NULL);
		}
		j++;
		i++;
	}
	cmd_args[j] = NULL;
	return (cmd_args);
}

// Function to extract redirections from tokens
t_redir *extract_redirections(char **tokens, int start, int end)
{
	t_redir *redir_list = NULL;
	t_type_redir redir_type;
	int i = start;

	while (i < end)
	{
		redir_type = check_redirection(tokens[i]);
		if (redir_type != NOT_REDIR)
		{
			if (i + 1 < end) // make sure we have a target
			{
				t_redir *new_redir = create_redir_node(redir_type, tokens[i + 1]);
				if (new_redir)
					add_redir_to_list(&redir_list, new_redir);
			}
			i += 2; // skip redirection operator and target
		}
		else
			i++;
	}
	return (redir_list);
}

// Function to parse input and create data structure
t_data *parse_input(char *input)
{
	char **tokens;
	t_data *head = NULL;
	t_data *current = NULL;
	int token_count = 0;
	int i = 0;
	int start = 0;
	int has_pipe = 0;

	if (!input || strlen(input) == 0)
		return (NULL);

	// Tokenize input
	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);

	// Count tokens and check for pipes
	while (tokens[token_count])
	{
		if (strcmp(tokens[token_count], "|") == 0)
			has_pipe = 1;
		token_count++;
	}

	// Parse tokens
	i = 0;
	start = 0;
	while (i <= token_count)
	{
		if (i == token_count || strcmp(tokens[i], "|") == 0)
		{
			// Create new data node
			t_data *new_data = create_data_node();
			if (!new_data)
				break;

			// Set node type
			if (has_pipe)
				new_data->type = PIPE_NODE;
			else
				new_data->type = CMD_NODE;

			// Extract command arguments
			new_data->cmd = extract_cmd_args(tokens, start, i);

			// Check for builtin
			if (new_data->cmd && new_data->cmd[0])
				new_data->builtin_type = check_builtin(new_data->cmd[0]);
			else
				new_data->builtin_type = NOT_BUILTIN;

			// Extract redirections
			new_data->redir = extract_redirections(tokens, start, i);

			// Add to list
			if (!head)
			{
				head = new_data;
				current = head;
			}
			else
			{
				current->next = new_data;
				current = new_data;
			}

			start = i + 1;
		}
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);

	return (head);
}

// Function to free the data structure
void free_data_structure(t_data *data)
{
	t_data *current = data;
	t_data *next;

	while (current)
	{
		next = current->next;

		// Free command array
		if (current->cmd)
		{
			int i = 0;
			while (current->cmd[i])
			{
				free(current->cmd[i]);
				i++;
			}
			free(current->cmd);
		}

		// Free redirections
		t_redir *redir = current->redir;
		t_redir *next_redir;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->target);
			free(redir);
			redir = next_redir;
		}

		free(current);
		current = next;
	}
}

void detect_heredoc_position(t_data *data, t_heredoc *heredoc, char *original_input)
{
	t_data *curr;
	t_data *heredoc_node = NULL;
	int node_count = 0;
	int heredoc_position = -1;
	int pos = 0;

	// Reset
	heredoc->before_hered = 0;
	heredoc->middle_hered = 0;
	heredoc->after_hered = 0;

	// Count nodes and find heredoc position
	curr = data;
	while (curr)
	{
		t_redir *redir = curr->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				heredoc_node = curr;
				heredoc_position = pos;
				break;
			}
			redir = redir->next;
		}
		node_count++;
		pos++;
		curr = curr->next;
	}

	if (!heredoc_node)
		return;

	// Check command count in heredoc node
	int cmd_args = 0;
	if (heredoc_node->cmd)
	{
		while (heredoc_node->cmd[cmd_args])
			cmd_args++;
	}

	// The key insight: regardless of pipeline position, we need to check
	// the heredoc position relative to commands in its own node
	
	if (cmd_args == 0)
	{
		// Only heredoc, no commands in this node
		// Need to check pipeline context
		if (node_count == 1)
		{
			heredoc->after_hered = 1; // "<< EOF" alone
		}
		else if (heredoc_position == 0)
		{
			heredoc->after_hered = 1; // "<< EOF | ..." - heredoc before pipeline
		}
		else if (heredoc_position == node_count - 1)
		{
			heredoc->before_hered = 1; // "... | << EOF" - heredoc after pipeline
		}
		else
		{
			heredoc->middle_hered = 1; // "... | << EOF | ..." - heredoc in middle
		}
	}
	else if (cmd_args == 1)
	{
		// Single command with heredoc in same node
		char *heredoc_pos = strstr(original_input, "<<");
		char *cmd_pos = NULL;
		
		if (heredoc_node->cmd[0])
			cmd_pos = strstr(original_input, heredoc_node->cmd[0]);
		
		if (heredoc_pos && cmd_pos)
		{
			if (cmd_pos < heredoc_pos)
			{
				// Command before heredoc: "ls << EOF" or "ls | cat << EOF"
				heredoc->before_hered = 1;
			}
			else
			{
				// Command after heredoc: "<< EOF ls" or "<< EOF ls | cat"
				heredoc->after_hered = 1;
			}
		}
		else
		{
			heredoc->before_hered = 1;
		}
	}
	else if (cmd_args >= 2)
	{
		// Multiple commands with heredoc: need to check if heredoc is truly in middle
		// We need to determine if there are commands both before AND after heredoc
		char *heredoc_pos = strstr(original_input, "<<");
		int commands_before = 0;
		int commands_after = 0;
		
		if (heredoc_pos && heredoc_node->cmd)
		{
			// Count commands before and after heredoc position
			for (int i = 0; i < cmd_args; i++)
			{
				char *cmd_pos = strstr(original_input, heredoc_node->cmd[i]);
				if (cmd_pos && cmd_pos < heredoc_pos)
					commands_before++;
				else if (cmd_pos && cmd_pos > heredoc_pos)
					commands_after++;
			}
		}
		
		if (commands_before > 0 && commands_after > 0)
		{
			// Commands both before and after: "ls << EOF cat"
			heredoc->middle_hered = 1;
		}
		else if (commands_before > 0)
		{
			// All commands before heredoc: "ls -l << EOF"
			heredoc->before_hered = 1;
		}
		else if (commands_after > 0)
		{
			// All commands after heredoc: "<< EOF ls -l"
			heredoc->after_hered = 1;
		}
		else
		{
			// Fallback
			heredoc->before_hered = 1;
		}
	}
}

int main(int argc, char **argv, char **env)
{
	char *input;
	t_data *parsed_data;
	t_heredoc *heredoc;

	while (1)
	{
		input = readline("minishell-3.2$~ ");
		if (!input)
			break;
		if (strlen(input) > 0)
			add_history(input);
		if (strlen(input) == 0)
		{
			free(input);
			continue;
		}
		parsed_data = parse_input(input);
		if (parsed_data)
		{
			heredoc = malloc(sizeof(t_heredoc));
			if (!heredoc)
			{
				perror("malloc");
				free_data_structure(parsed_data);
				free(input);
				continue;
			}
			detect_heredoc_position(parsed_data, heredoc, input);

			ft_exec(parsed_data, env, heredoc);
			free(heredoc);
			free_data_structure(parsed_data);
		}
		free(input);
	}
	return (0);
}

