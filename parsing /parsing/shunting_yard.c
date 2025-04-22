/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:16:09 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 01:23:56 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void add_front_ops_stack(t_ready_token **head, t_ready_token *node) { /* ... */ }
void push_to_postfix(t_ready_token **head, t_ready_token *node) { /* ... */ }
t_ready_token *pop_infix_note(t_parser *parser) { /* ... */ }
t_ready_token *pop_op_stack_note(t_parser *parser) { /* ... */ }
void op_to_postfix(t_ready_token *op, t_parser *parser) { /* ... */ }
void shunting_yard(t_parser *parser) { /* ... */ }