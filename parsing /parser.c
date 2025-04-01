/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/01 23:50:02 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

// TODO day 0
/* Lexer initialization */
t_lexer         *init_lexer(const char *input);

/* Token creation/destruction */
t_token         *create_token(t_token_type type, char *value);
void            free_token(t_token *token);

// TODO day 1
/* Lexer operations */
void            advance_lexer(t_lexer *lexer);
void            skip_whitespace(t_lexer *lexer);
char            *collect_word(t_lexer *lexer);

/* Main tokenization */
t_token         *get_next_token(t_lexer *lexer);

// TODO day 2
/* Token classification */
t_token_type    classify_token(char *value);

/* Specialized collectors */
char            *collect_quoted(t_lexer *lexer, char quote);
char            *collect_operator(t_lexer *lexer);
bool            is_operator(char c);

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	return (0);
}
