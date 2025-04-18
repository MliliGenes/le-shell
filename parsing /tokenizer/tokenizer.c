/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:27:08 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/18 01:04:09 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

bool	is_white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

bool	is_op(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE);
}

bool	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

bool	is_word(t_token_type type)
{
	return (type == TOKEN_COMMAND || type == TOKEN_ARG);
}

bool	is_paren(t_token_type type)
{
	return (type == TOKEN_PL || type == TOKEN_PR);
}

bool	has_quotes(char *token)
{
	while (token && *token)
	{
		if (*token == '\'' || *token == '"')
			return (true);
		token++;
	}
	return (false);
}

bool	is_var(char *chunk)
{
	int	i;

	i = 0;
	return (chunk[i] == '$' && chunk[i + 1]);
}

bool	has_var(char *token)
{
	int	i;
	bool d_quoted;

	i = 0;
	d_quoted = false;
	while (token && token[i])
	{
		if (token[i] == '"')
		{
			d_quoted = !d_quoted;
			i++;
		}
		if (!d_quoted && token[i] == '\'')
		{
			i++;
			while (token[i] != '\'')
				i++;
		}
		if (token[i] == '$' && (token[i + 1] && token[i + 1] != '"'
				&& !is_white_space(token[i + 1])))
			return (true);
		i++;
	}
	return (false);
}

bool	is_full_operator(t_lexer *lexer)
{
	char	c;
	char	next;

	c = lexer->current_char;
	if (c == '(' || c == ')')
		return (true);
	if (c == '|' || c == '&' || c == '<' || c == '>')
	{
		next = lexer->input[lexer->pos + 1];
		if ((c == '|' && next == '|') || (c == '&' && next == '&') || (c == '<'
				&& next == '<') || (c == '>' && next == '>'))
			return (true);
		if (c == '|' || c == '<' || c == '>')
			return (true);
	}
	return (false);
}

/* Lexer initialization */
t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->current_char = lexer->input[0];
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	return (lexer);
}

/* Token creation/destruction */
t_token	*create_token(t_token_type type, char *value)
{
	t_token		*token;
	static int	index;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->n_index = index++;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_back_token(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (!head || !node)
		return ;
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

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free_token(head);
		head = tmp;
	}
}

/* Lexer operations */
void	advance_lexer(t_lexer *lexer)
{
	if (lexer->pos < lexer->len)
	{
		lexer->pos++;
		lexer->current_char = lexer->input[lexer->pos];
	}
}

int	check_quotes_balance(const char *input)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote)
		return (1);
	if (in_double_quote)
		return (2);
	return (0);
}

static void	skip_quotes(char c, int *quotes)
{
	if (c == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
	else if (c == '"' && !quotes[0])
		quotes[1] = !quotes[1];
}

int	check_parenthesis_balance(const char *input)
{
	int	i;
	int	data[3];

	i = 0;
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	while (input[i])
	{
		skip_quotes(input[i], data);
		if (!data[0] && !data[1])
		{
			if (input[i] == '(')
				data[2]++;
			else if (input[i] == ')')
			{
				data[2]--;
				if (data[2] < 0)
					return (1);
			}
		}
		i++;
	}
	return (data[2] != 0);
}

bool	check_m_percent(char *input)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote && input[i] == '&')
		{
			if (input[i + 1] != '&')
				return (true);
			else
				i += 2;
		}
		i++;
	}
	return (false);
}

// skipping spaces
void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && is_white_space(lexer->current_char))
		advance_lexer(lexer);
}

t_token_type	classify_operator(char *op)
{
	if (ft_strcmp(op, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(op, "||") == 0)
		return (TOKEN_OR);
	if (ft_strcmp(op, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(op, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(op, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(op, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(op, ">>") == 0)
		return (TOKEN_APPEND);
	if (ft_strcmp(op, "(") == 0)
		return (TOKEN_PL);
	if (ft_strcmp(op, ")") == 0)
		return (TOKEN_PR);
	return (TOKEN_WORD);
}

// collect words
t_token	*handle_word(t_lexer *lexer)
{
	t_token	*token;
	char	*value;
	int		start;

	start = lexer->pos;
	while (lexer->pos < lexer->len && !is_white_space(lexer->current_char)
		&& !is_operator(lexer->current_char))
		advance_lexer(lexer);
	value = ft_strndup(lexer->input + start, lexer->pos - start);
	if (!value)
		return (NULL);
	token = create_token(TOKEN_WORD, value);
	return (token);
}

t_token	*handle_quoted(t_lexer *lexer)
{
	t_token	*token;
	char	*value;
	char	quote_type;
	int		start;

	start = lexer->pos;
	quote_type = lexer->current_char;
	advance_lexer(lexer);
	while (lexer->current_char != quote_type && lexer->pos < lexer->len)
		advance_lexer(lexer);
	if (lexer->current_char != quote_type)
		return (NULL);
	advance_lexer(lexer);
	while (lexer->current_char && !is_white_space(lexer->current_char)
		&& !is_operator(lexer->current_char))
		advance_lexer(lexer);
	value = ft_strndup(lexer->input + start, lexer->pos - start);
	if (!value)
		return (NULL);
	;
	token = create_token(TOKEN_WORD, value);
	return (token);
}

t_token	*handle_operator(t_lexer *lexer)
{
	char	op[3];
	int		op_len;
	t_token	*token;
	char	*op_str;

	if (lexer->pos + 1 < lexer->len)
	{
		op[0] = lexer->current_char;
		op[1] = lexer->input[lexer->pos + 1];
		if ((op[0] == '>' && op[1] == '>') || (op[0] == '<' && op[1] == '<')
			|| (op[0] == '|' && op[1] == '|') || (op[0] == '&' && op[1] == '&'))
			op_len = 2;
		else
		{
			op_len = 1;
			op[1] = '\0';
		}
	}
	else
	{
		op_len = 1;
		op[0] = lexer->current_char;
	}
	op_str = ft_strndup(op, op_len);
	if (!op_str)
		return (NULL);
	advance_lexer(lexer);
	if (op_len == 2)
		advance_lexer(lexer);
	token = create_token(classify_operator(op_str), op_str);
	if (!token)
		free(op_str);
	return (token);
}

/* Main tokenization */
t_token	*get_next_token(t_lexer *lexer)
{
	skip_whitespace(lexer);
	if (lexer->current_char == '\0')
		return (create_token(TOKEN_EOF, NULL));
	if (lexer->current_char == '\'' || lexer->current_char == '"')
		return (handle_quoted(lexer));
	if (is_operator(lexer->current_char) && is_full_operator(lexer))
		return (handle_operator(lexer));
	return (handle_word(lexer));
}

void	create_tokens_list(t_lexer *lexer, t_token **head)
{
	t_token	*token;

	while (true)
	{
		token = get_next_token(lexer);
		// if (!token)
		// free and retuen
		if (token->type == TOKEN_EOF)
		{
			add_back_token(head, token);
			break ;
		}
		add_back_token(head, token);
	}
}

int	validate_tokens(t_token *head)
{
	while (head->type != TOKEN_EOF)
	{
		if (is_redir(head->type) && (!head->next
				|| head->next->type != TOKEN_WORD))
			return (1);
		if (is_op(head->type) && head->next && is_op(head->next->type))
			return (1);
		if (is_redir(head->type) && head->next && is_redir(head->next->type))
			return (1);
		if (head->type == TOKEN_PL && head->next && (is_op(head->next->type)
				|| head->next->type == TOKEN_PR))
			return (1);
		if (head->type == TOKEN_PR && head->next && !is_op(head->next->type)
			&& !is_redir(head->next->type) && head->next->type != TOKEN_PR
			&& head->next->type != TOKEN_EOF)
			return (1);
		if (head->n_index > 0 && head->type == TOKEN_PL && head->prev
			&& !is_op(head->prev->type) && head->prev->type != TOKEN_PL)
			return (1);
		if ((head->n_index == 0 && is_op(head->type)) || (is_op(head->type)
				&& head->next && head->next->type == TOKEN_EOF))
			return (1);
		head = head->next;
	}
	return (0);
}

void	classify_tokens(t_token *head)
{
	bool	is_cmd_found;

	is_cmd_found = false;
	while (head->type != TOKEN_EOF)
	{
		if (head->type == TOKEN_WORD && head->prev
			&& is_redir(head->prev->type))
			head->type = TOKEN_FILE;
		if (!is_cmd_found && ((head->n_index == 0 && head->type == TOKEN_WORD)
				|| (head->type == TOKEN_WORD && head->prev
					&& (is_op(head->prev->type)
						|| head->prev->type == TOKEN_PL))
				|| (head->type == TOKEN_WORD && head->prev
					&& head->prev->type == TOKEN_FILE)))
		{
			head->type = TOKEN_COMMAND;
			is_cmd_found = true;
		}
		if (head->type == TOKEN_WORD)
			head->type = TOKEN_ARG;
		if (is_op(head->type))
			is_cmd_found = false;
		head = head->next;
	}
}

void	trim_quotes(t_token *head)
{
	while (head && head->type != TOKEN_EOF)
	{
		if (is_word(head->type) && has_var(head->value))
		{
			
		}
		head = head->next;
	}
}