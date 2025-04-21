/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/21 04:51:00 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

int	get_op_precedence(t_ready_token *token)
{
	t_op_type	op_type;

	op_type = ((t_op *)token->p_token)->type;
	if (op_type == OP_AND)
		return (2); 
	else if (op_type == OP_OR)
		return (1);
	else if (op_type == OP_PIPE)
		return (3);
	else if (op_type == OP_PAREN_L || op_type == OP_PAREN_R)
		return (0);
	return (-1);
}

void	add_front_ops_stack(t_ready_token **head, t_ready_token *node)
{
	if (!head || !node)
		return ;
	node->prev = NULL;
	node->next = *head;
	if (*head)
		(*head)->prev = node;
	*head = node;
}

void	push_to_postfix(t_ready_token **head, t_ready_token *node)
{
	node->next = NULL;
	node->prev = NULL;
	add_back_ready_token(head, node);
}

void	ll(void)
{
	system("leaks parser");
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

t_ready_token	*pop_infix_note(t_parser *parser)
{
	t_ready_token	*popped_node;

	if (!parser || !parser->infix_note)
		return (NULL);
	popped_node = parser->infix_note;
	parser->infix_note = parser->infix_note->next;
	if (parser->infix_note)
		parser->infix_note->prev = NULL;
	popped_node->next = NULL;
	return (popped_node);
}

t_ready_token	*pop_op_stack_note(t_parser *parser)
{
	t_ready_token	*popped_node;

	if (!parser || !parser->ops_stack)
		return (NULL);
	popped_node = parser->ops_stack;
	parser->ops_stack = parser->ops_stack->next;
	if (parser->ops_stack)
		parser->ops_stack->prev = NULL;
	popped_node->next =NULL;
	return (popped_node);
}

void	op_to_postfix(t_ready_token *op, t_parser *parser)
{
	t_ready_token	*tmp_op;

	while (parser->ops_stack
		&& get_op_precedence(parser->ops_stack) > get_op_precedence(op))
	{
		tmp_op = pop_op_stack_note(parser);
		push_to_postfix(&parser->postfix_note, tmp_op);
	}
	add_front_ops_stack(&parser->ops_stack, op);
}

void	shunting_yard(t_parser *parser)
{
	t_ready_token	*current_node;

	if (!parser || !parser->infix_note)
		return ;
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

bool	check_input(char *input)
{
	return (check_quotes_balance(input) || check_parenthesis_balance(input)
		|| check_m_percent(input));
}

void	print_postfix_notation(t_ready_token *head)
{
	t_ready_token	*current;
	t_cmd			*cmd;
	t_op			*op;

	current = head;
	while (current)
	{
		if (current->type == CMD)
		{
			cmd = (t_cmd *)current->p_token;
			printf("%s ", cmd->cmd);
		}
		else if (current->type == OP)
		{
			op = (t_op *)current->p_token;
			if (op->type == OP_PIPE)
				printf("| ");
			else if (op->type == OP_AND)
				printf("&& ");
			else if (op->type == OP_OR)
				printf("|| ");
			else if (op->type == OP_PAREN_L)
				printf("( ");
			else if (op->type == OP_PAREN_R)
				printf(") ");
		}
		current = current->next;
	}
	printf("\n");
}

int	main(void)
{
	t_lexer		*lexer;
	t_token		*tokens;
	t_parser	*parser;

	// atexit(ll);
	if (check_input(TEST))
		return (1);
	lexer = NULL;
	tokens = NULL;
	parser = NULL;
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (!tokens->value || validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), 1);
	parser = init_parser();
	if (!parser)
		return (1);
	classify_tokens(tokens);
	extract_tokens(tokens, &parser->infix_note);
	print_postfix_notation(parser->infix_note);
	shunting_yard(parser);
	print_postfix_notation(parser->postfix_note);
	print_ready_tokens(parser->postfix_note);
	// print_tokens(tokens);
	// free_ready_tokens_list(ready_tokens);
	free_token_list(tokens);
	free(lexer);
	return (0);
}
