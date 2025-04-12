/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:14:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/12 18:06:24 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"

# ifndef TEST
#  define TEST "(ls -la | grep \"txt\" > text_files.list && (cat < Makefile -e) ) && echo \"Text files found:\" && cat text_files.list || (echo \"No text files found\" >> error.log && exit 1) | wc -l < input.txt >> results.log"
// #  define TEST "ls | | wc -l | grep"
# endif

t_token	*create_token(t_token_type type, char *value);
void	free_token(t_token *token);
t_lexer	*init_lexer(char *input);
void	advance_lexer(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
t_token	*handle_word(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
void	classify_tokens(t_token *head);

#endif