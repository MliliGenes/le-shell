/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:09:12 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 01:23:35 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

bool is_white_space(char c) { /* ... */ }
bool is_operator(char c) { /* ... */ }
bool is_op(t_token_type type) { /* ... */ }
bool is_redir(t_token_type type) { /* ... */ }
bool is_word(t_token_type type) { /* ... */ }
bool is_paren(t_token_type type) { /* ... */ }
bool has_quotes(char *token) { /* ... */ }
bool is_full_operator(t_lexer *lexer) { /* ... */ }
t_token_type classify_operator(char *op) { /* ... */ }
void classify_tokens(t_token *head) { /* ... */ }