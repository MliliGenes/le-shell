/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:14:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/14 01:38:23 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"

# ifndef TEST
// #  define TEST "<< \"$HOME\""
#  define TEST "(ls -la | grep \"txt\" > \"text_files\" && (cat < Makefile-e) ) && echo \"Text files found:\" && cat text_files.list|| (echo \"No text files found\" >> error.log && exit 1) | wc -l < input.txt >> results.log"
# endif

t_lexer			*init_lexer(char *input);
void			advance_lexer(t_lexer *lexer);
void			skip_whitespace(t_lexer *lexer);

t_token			*create_token(t_token_type type, char *value);
void			add_back_token(t_token **head, t_token *node);
void			free_token(t_token *token);
void			free_token_list(t_token *head);

bool			is_white_space(char c);
bool			is_operator(char c);
bool			is_op(t_token_type type);
bool			is_redir(t_token_type type);
bool			is_paren(t_token_type type);
bool			is_full_operator(t_lexer *lexer);
t_token_type	classify_operator(char *op);

t_token			*get_next_token(t_lexer *lexer);
t_token			*handle_word(t_lexer *lexer);
t_token			*handle_quoted(t_lexer *lexer);
t_token			*handle_operator(t_lexer *lexer);
void			create_tokens_list(t_lexer *lexer, t_token **head);

int				check_quotes_balance(const char *input);
int				check_parenthesis_balance(const char *input);
bool			check_m_percent(char *input);
int				validate_tokens(t_token *head);
void			classify_tokens(t_token *head);

#endif