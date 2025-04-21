/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:14:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/21 05:55:46 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"

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
bool			is_word(t_token_type type);
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

t_op_type		token_to_op_type(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);

t_redir			*create_redir_node(t_redir_type type, char *file_or_limiter);
t_cmd			*create_cmd_node(char **args, t_redir *redirs);
t_op			*create_op_node(t_op_type type);
t_ready_token	*create_ready_token_node(void *token, int type);

void			add_back_redir_node(t_redir **head, t_redir *node);
void			add_back_ready_token(t_ready_token **head, t_ready_token *node);

void			free_args_array(char **args, int count);
void			free_redirs(t_redir *redirs);
static int		count_args_in_cmd(char **args);
void			free_ready_tokens_list(t_ready_token *head);

t_redir			*get_redirs(t_token *start, t_token *end);
bool			has_redirections(t_token *start, t_token *end);
int				count_args(t_token *start, t_token *end);
char			**get_args(t_token *start, t_token *end);
t_cmd			*extract_cmd_data(t_token *start, t_token *end);

bool			process_command_segment(t_token *start, t_token *end,
					t_ready_token **head);
bool			add_operator_to_list(t_token *current, t_ready_token **head);
bool			extract_tokens(t_token *tokens, t_ready_token **head);

#endif
