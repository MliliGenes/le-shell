/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/09 18:26:49 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

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
	return (type == TOKEN_REDIR_IN || type == TOKEN_HEREDOC
		|| type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}

bool	is_paren(t_token_type type)
{
	return (type == TOKEN_PAREN_L || type == TOKEN_PAREN_R);
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
t_token	*create_token(t_token_type type, char *value, int start, int end)
{
	t_token		*token;
	static int	index;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->n_index = index++;
	token->start_pos = start;
	token->end_pos = end;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_back_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
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
		return (TOKEN_PAREN_L);
	if (ft_strcmp(op, ")") == 0)
		return (TOKEN_PAREN_R);
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
	token = create_token(TOKEN_WORD, value, start, lexer->pos - 1);
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
	while (!is_white_space(lexer->current_char)
		&& !is_operator(lexer->current_char))
		advance_lexer(lexer);
	value = ft_strndup(lexer->input + start, lexer->pos - start);
	if (!value)
		return (NULL);
	;
	token = create_token(TOKEN_WORD, value, start, lexer->pos - 1);
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
	token = create_token(classify_operator(op_str), op_str, lexer->pos,
			lexer->pos + op_len);
	if (!token)
		free(op_str);
	return (token);
}

/* Main tokenization */
t_token	*get_next_token(t_lexer *lexer)
{
	skip_whitespace(lexer);
	if (lexer->current_char == '\0')
		return (create_token(TOKEN_EOF, NULL, lexer->pos, lexer->pos));
	if (lexer->current_char == '\'' || lexer->current_char == '"')
		return (handle_quoted(lexer));
	if (is_operator(lexer->current_char) && is_full_operator(lexer))
		return (handle_operator(lexer));
	return (handle_word(lexer));
}

// TODO day 2
/* Token classification */
t_token_type	classify_token(char *value);

/* Specialized collectors */
// char			*collect_quoted(t_lexer *lexer, char quote);
// char			*collect_operator(t_lexer *lexer);
// bool			is_operator(char c);
void	ll(void)
{
	system("leaks parser");
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lexer;
	t_token	*head;
	t_token	*token;
	t_token	*tmp;

	// atexit(ll);
	(void)ac;
	(void)av;
	(void)envp;
	head = NULL;
	lexer = init_lexer("(ls) || saad || (cat file1.txt) >> ls | echo\t\t\t \"$hello\"'world'>test < infile.txt cat file2.txt ");
	if (!lexer || check_quotes_balance(lexer->input)
		|| check_parenthesis_balance(lexer->input))
		return (1);
	// TODO create tokens list function ();
	while (true)
	{
		token = get_next_token(lexer);
		if (token->type == TOKEN_EOF)
		{
			add_back_token(&head, token);
			break ;
		}
		add_back_token(&head, token);
	}
	// TODO validate the syntax function ();
	while (head->type != TOKEN_EOF)
	{
		if (is_op(head->type) && is_op(head->next->type))
			return (1);
		if (is_redir(head->type) && is_redir(head->next->type))
			return (1);
		if (head->type == TOKEN_PAREN_L && is_op(head->next->type))
			return (1);
		if (head->type == TOKEN_PAREN_R && !is_op(head->next->type)
			&& !is_redir(head->next->type))
			return (1);
		if (head->n_index > 0 && head->type == TOKEN_PAREN_L
			&& !is_op(head->prev->type))
			return (1);
		if (head->n_index == 0 && is_op(head->type))
			return (1);
		head = head->next;
	}
	while (head->prev)
		head = head->prev;
	tmp = head;
	while (tmp)
	{
		printf("Token		#%d\n", tmp->n_index);
		printf("Value		:%s\n", tmp->value);
		printf("Type		:%d\n", tmp->type);
		printf("Start Pos	:%d\n", tmp->start_pos);
		printf("End Pos		:%d\n", tmp->end_pos);
		printf("\n");
		tmp = tmp->next;
	}
	free_token_list(head);
	free(lexer);
	return (0);
}

// printf("Token #%d\n", token->n_index);
// printf("Value     : %s\n", token->value);
// printf("Type      : %d\n", token->type);
// printf("Start Pos : %d\n", token->start_pos);
// printf("End Pos   : %d\n", token->end_pos);
// printf("\n");