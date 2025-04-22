/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:15:38 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 12:41:58 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	shunting_yard(t_parser *parser)
{
	t_ready_token	*current_node;

	while (parser->infix_note)
	{
		current_node = pop_infix_note(parser);
		if (current_node->type == CMD)
			push_to_postfix(&parser->postfix_note, current_node);
		else if (current_node->type == OP)
			op_to_postfix(current_node, parser);
	}
	while (parser->ops_stack)
	{
		current_node = pop_op_stack_note(parser);
		if (((t_op *)current_node->p_token)->type != OP_PAREN_L)
			push_to_postfix(&parser->postfix_note, current_node);
	}
}

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->infix_note = NULL;
	parser->postfix_note = NULL;
	parser->ops_stack = NULL;
	return (parser);
}

// TODO t_ast *parse_input(t_token *tokens) { /* ... */ }