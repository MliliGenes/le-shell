/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/19 23:55:41 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	add_front_ops_queue(t_ready_token **head, t_ready_token *node)
{
	if (!head || !node)
		return ;
	node->prev = NULL;
	node->next = *head;
	if (*head)
		(*head)->prev = node;
	*head = node;
}

void	ll(void)
{
	system("leaks parser");
}

t_parser	*init_parser(t_ready_token *head)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (parser)
		return (NULL);
	parser->infix_note = head;
	parser->postfix_note = NULL;
	parser->ops_stack = NULL;
	return (parser);
}

void	build_post_fix(t_parser *parser)
{
	t_op			*op;
	t_cmd			*cmd;
	t_ready_token	*head;

	if (!parser)
		return ;
	head = parser->infix_note;
	while (head)
	{
		if (head->type == CMD)
		{
			cmd = (t_cmd *)head->p_token;
			// TODO: push to post fix parser->postfix_note
		}
		else if (head->type == OP)
		{
			op = (t_op *)head->p_token;
			if (op->type == OP_PAREN_R)
				return ;
			// pop all ops till the open parent
		}
		head = head->next;
	}
}

bool	check_balance(char *input)
{
	return (check_quotes_balance(input) || check_parenthesis_balance(input)
		|| check_m_percent(input));
}

int	main(void)
{
	t_lexer			*lexer;
	t_token			*tokens;
	t_ready_token	*ready_tokens;
	t_parser		*parser;

	atexit(ll);
	if (check_balance(TEST))
		return (1);
	lexer = NULL;
	tokens = NULL;
	ready_tokens = NULL;
	parser = NULL;
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), 1);
	classify_tokens(tokens);
	extract_tokens(tokens, &ready_tokens);
	parser = init_parser(ready_tokens);
	if (!parser)
		return (1);
	// trim_quotes(tokens); TODO
	// print_tokens(tokens);
	// print_ready_tokens(ready_tokens);
	free_ready_tokens_list(ready_tokens);
	free_token_list(tokens);
	free(lexer);
	return (0);
}
