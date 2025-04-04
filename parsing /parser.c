/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/04 21:16:53 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '('
		|| c == ')');
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
t_lexer	*init_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = ft_strdup(input);
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
	token->next = NULL;
	token->n_index = index++;
	return (token);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
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

// skipping spaces
void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && lexer->current_char == ' ')
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
	while (lexer->pos < lexer->len && lexer->current_char != ' '
		&& !(is_operator(lexer->current_char) || lexer->current_char == '\''
			|| lexer->current_char == '\"'))
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
	value = ft_strndup(lexer->input + start, lexer->pos - start);
	if (!value)
		return (NULL);
	token = create_token(TOKEN_WORD, value);
	return (token);
}

t_token	*handle_operator(t_lexer *lexer)
{
	char	op[3] = {0};
	int		op_len;
	t_token	*token;
	char	*op_str;

	if (lexer->pos + 1 < lexer->len)
	{
		op[0] = lexer->current_char;
		op[1] = lexer->input[lexer->pos + 1];
		if ((op[0] == '>' && op[1] == '>') || (op[0] == '<' && op[1] == '<')
			|| (op[0] == '|' && op[1] == '|') || (op[0] == '&' && op[1] == '&'))
		{
			op_len = 2;
		}
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
	for (int i = 0; i < op_len; i++)
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

// TODO day 2
/* Token classification */
t_token_type	classify_token(char *value);

/* Specialized collectors */
// char			*collect_quoted(t_lexer *lexer, char quote);
// char			*collect_operator(t_lexer *lexer);
// bool			is_operator(char c);

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lexer;
	t_token	*token;

	(void)ac;
	(void)av;
	(void)envp;
	// i need to collect the quotes
	lexer = init_lexer("echo | awdawd\"$hello\"dawd||file1.txt | | < infile.txt 'cat file2.txt'");
	if (!lexer)
		return (1);
	token = get_next_token(lexer);
	while (token && token->value)
	{
		printf("index: %d\ntoken: %s\ntype: %d\n\n", token->n_index,
			token->value, token->type);
		token = get_next_token(lexer);
	}
	return (0);
}
