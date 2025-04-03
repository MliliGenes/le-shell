/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/03 16:11:28 by sel-mlil         ###   ########.fr       */
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
	if (c == ';' || c == '(' || c == ')')
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
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
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

// collect words
char	*collect_word(t_lexer *lexer)
{
	int	start;
	int	length;

	start = lexer->pos;
	while (lexer->pos < lexer->len && lexer->current_char != ' '
		&& !is_operator(lexer->current_char))
		advance_lexer(lexer);
	length = lexer->pos - start;
	return (strndup(lexer->input + start, length));
}

/* Main tokenization */
t_token			*get_next_token(t_lexer *lexer);

// TODO day 2
/* Token classification */
t_token_type	classify_token(char *value);

/* Specialized collectors */
char			*collect_quoted(t_lexer *lexer, char quote);
char			*collect_operator(t_lexer *lexer);
bool			is_operator(char c);

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lexer;

	(void)ac;
	(void)av;
	(void)envp;
	lexer = init_lexer("echo hello > file1.txt || < infile.txt cat file2.txt");
	if (!lexer)
		return (1);
	return (0);
}
