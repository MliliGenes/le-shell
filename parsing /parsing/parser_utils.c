/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:16:26 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 01:24:05 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

int get_op_precedence(t_ready_token *token) { /* ... */ }
bool check_input(char *input) { /* ... */ }
void ll(void) { /* ... */ }
void print_notation(t_ready_token *head) { /* ... */ }
static void print_indentation(int level) { /* ... */ }
static void print_ast_readable_recursive(t_ast *root, int level) { /* ... */ }
void print_ast(t_ast *root) { /* ... */ }