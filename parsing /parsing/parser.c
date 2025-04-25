/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:15:38 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/24 20:34:30 by le-saad          ###   ########.fr       */
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
	parser->holy_tree = NULL;
	return (parser);
}

static void	index_linked(t_token *token)
{
	int	i;

	i = 0;
	while (token->type != TOKEN_EOF)
	{
		token->n_index = i++;
		token = token->next;
	}
}

t_ready_token	*cmd_line_to_ready_tokens(char *cmd_line)
{
	t_lexer			*lexer;
	t_token			*tokens;
	t_ready_token	*ready_tokens;

	tokens = NULL;
	lexer = init_lexer(cmd_line);
	if (!lexer)
		return (NULL);
	create_tokens_list(lexer, &tokens);
	index_linked(tokens);
	if (!tokens->value || validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), NULL);
	classify_tokens(tokens);
	ready_tokens = NULL;
	extract_tokens(tokens, &ready_tokens);
	// print_ready_tokens(ready_tokens);
	free_token_list(tokens);
	free(lexer);
	return (ready_tokens);
}

t_parser	*parse_input(char *cmd_line)
{
	t_parser	*parser;

	parser = init_parser();
	if (!parser)
		return (NULL);
	if (!cmd_line || check_input(cmd_line))
		return (NULL);
	parser->infix_note = cmd_line_to_ready_tokens(cmd_line);
	shunting_yard(parser);
	parser->holy_tree = post_to_tree(parser->postfix_note);
	return (parser);
}
