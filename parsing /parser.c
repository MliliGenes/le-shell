/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/15 17:42:21 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

t_op_type	token_to_op_type(t_token_type type)
{
	if (type == TOKEN_PL)
		return (OP_PAREN_L);
	if (type == TOKEN_PR)
		return (OP_PAREN_R);
	if (type == TOKEN_PIPE)
		return (OP_PIPE);
	if (type == TOKEN_AND)
		return (OP_AND);
	if (type == TOKEN_OR)
		return (OP_OR);
	return (-1);
}

// Convert token type to redirection type
t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	else if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

t_redir	*create_redir_node(t_redir_type type, char *file_or_limiter)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir || !file_or_limiter)
		return (NULL);
	redir->type = type;
	redir->file_or_limiter = file_or_limiter;
	redir->next = NULL;
	return (redir);
}

void	add_back_redir_node(t_redir **head, t_redir *node)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_cmd	*create_cmd_node(char **args, t_redir *redirs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->cmd = NULL;
	if (args)
		cmd->cmd = args[0];
	cmd->redirs = redirs;
	cmd->fds[0] = 0;
	cmd->fds[1] = 1;
	return (cmd);
}

t_op	*create_op_node(t_op_type type)
{
	t_op	*op;

	op = malloc(sizeof(t_cmd));
	if (!op)
		return (NULL);
	op->type = type;
	return (op);
}

t_ready_token	*create_ready_token_node(void *token, int type)
{
	t_ready_token	*r_token;

	r_token = malloc(sizeof(t_ready_token));
	if (!r_token || !token)
		return (NULL);
	r_token->p_token = token;
	r_token->type = type;
	r_token->next = NULL;
	r_token->prev = NULL;
	return (r_token);
}

void	add_back_ready_token(t_ready_token **head, t_ready_token *node)
{
	t_ready_token	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

// Free arguments array
void	free_args_array(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

// Free redirection list
void	free_redirs(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs;
		redirs = redirs->next;
		free(temp->file_or_limiter);
		free(temp);
	}
}

t_redir	*get_redirs(t_token *start, t_token *end)
{
	t_redir	*redirs;
	t_redir	*redir_node;

	redirs = NULL;
	while (start && (end == NULL || start <= end))
	{
		if (is_redir(start->type))
		{
			redir_node = create_redir_node(token_to_redir_type(start->type),
					ft_strdup(start->next->value));
			if (!redir_node)
			{
				free_redirs(redirs);
				return (NULL);
			}
			add_back_redir_node(&redirs, redir_node);
		}
		start = start->next;
	}
	return (redirs);
}

bool	has_redirections(t_token *start, t_token *end)
{
	while (start && (end == NULL || start <= end))
	{
		if (is_redir(start->type))
			return (true);
		start = start->next;
	}
	return (false);
}

int	count_args(t_token *start, t_token *end)
{
	int	size;

	size = 0;
	while (start && (end == NULL || start <= end))
	{
		if (is_word(start->type))
			size++;
		start = start->next;
	}
	return (size);
}

char	**get_args(t_token *start, t_token *end)
{
	char	**args;
	int		i;

	if (!count_args(start, end))
		return (NULL);
	
	args = malloc(sizeof(char *) * (count_args(start, end) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (start && (end == NULL || start <= end))
	{
		if (is_word(start->type))
		{
			args[i++] = ft_strdup(start->value);
			if (!args[i - 1])
			{
				while (--i >= 0)
					free(args[i]);
				return (free(args), NULL);
			}
		}
		start = start->next;
	}
	return (args[i] = NULL, args);
}

t_cmd	*extract_cmd_data(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	char	**args;
	t_redir	*redirs;

	args = NULL;
	redirs = NULL;
	if (!start || start->type == TOKEN_EOF)
		return (NULL);
	redirs = get_redirs(start, end);
	args = get_args(start, end);
	if (!args && !redirs)
		return (NULL);
	cmd = create_cmd_node(args, redirs);
	if (!cmd)
	{
		if (args)
		{
			for (int i = 0; args[i]; i++)
				free(args[i]);
			free(args);
		}
		free_redirs(redirs);
	}
	return (cmd);
}

bool	process_command_segment(t_token *start, t_token *end,
		t_ready_token **head)
{
	t_cmd			*cmd;
	t_ready_token	*cmd_token;

	cmd = extract_cmd_data(start, end);
	if (!cmd)
		return (false);
	cmd_token = create_ready_token_node(cmd, CMD);
	if (!cmd_token)
		return (false);
	add_back_ready_token(head, cmd_token);
	return (true);
}

bool	add_operator_to_list(t_token *current, t_ready_token **head)
{
	t_op			*op_node;
	t_ready_token	*op_token;

	op_node = create_op_node(token_to_op_type(current->type));
	if (!op_node)
		return (false);
	op_token = create_ready_token_node(op_node, OP);
	if (!op_token)
		return (false); // freeing op_node
	add_back_ready_token(head, op_token);
	return (true);
}

bool	extract_tokens(t_token *tokens, t_ready_token **head)
{
	t_token	*cmd_start;
	t_token	*current;

	cmd_start = tokens;
	current = tokens;
	while (current->type != TOKEN_EOF)
	{
		if (is_op(current->type) || current->type == TOKEN_PL
			|| current->type == TOKEN_PR)
		{
			if (current != cmd_start)
				process_command_segment(cmd_start, current->prev, head);
			add_operator_to_list(current, head);
			cmd_start = current->next;
		}
		current = current->next;
	}
	if (cmd_start && cmd_start->type != TOKEN_EOF)
		process_command_segment(cmd_start, NULL, head);
	return (true);
}

void	ll(void)
{
	system("leaks parser");
}

int	main(void)
{
	t_lexer			*lexer;
	t_token			*tokens;
	t_ready_token	*ready_tokens;

	// atexit(ll);
	tokens = NULL;
	ready_tokens = NULL;
	if (check_quotes_balance(TEST) || check_parenthesis_balance(TEST)
		|| check_m_percent(TEST))
		return (1);
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (validate_tokens(tokens))
		return (1);
	classify_tokens(tokens);
	print_tokens(tokens);
	extract_tokens(tokens, &ready_tokens);
	print_ready_tokens(ready_tokens);
	free(lexer);
	return (0);
}
