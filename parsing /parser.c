/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/22 13:56:10 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks parser");
}

void	print_notation(t_ready_token *head)
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

# ifndef TEST
#  define TEST "(ls -la || hghgdhg) && ls -la | grep hjhjh && (hi && hiii)"
// #  define TEST "( ls *.c > \"testing\"'$the'test\"\"\"\"'''''''''''''''' -e | \"$grep\" \"$txt\" > \"text_files\" ) && ( cat < Makefile-e) && echo \"Text files found\"&& cat text_files.list|| (echo \"$No text files found\" >> error.log && exit 1) | wc -l < input.txt >> results.log"
# endif


void free_ast(t_ast *root)
{
	if (!root)
		return;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
}

int	main(void)
{
	t_lexer		*lexer;
	t_token		*tokens;
	
	t_parser	*parser;
	t_ast		*holy_tree;

	atexit(ll);
	if (check_input(TEST))
		return (1);
	lexer = NULL;
	tokens = NULL;
	parser = NULL;
	holy_tree = NULL;
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (!tokens->value || validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), 1);
	classify_tokens(tokens);
	parser = init_parser();
	if (!parser)
		return (free(lexer), free_token_list(tokens), 1);
	extract_tokens(tokens, &parser->infix_note);
	print_notation(parser->infix_note);
	shunting_yard(parser);
	print_notation(parser->postfix_note);
	holy_tree = post_to_tree(parser->postfix_note);
	print_ast(holy_tree);
	free_ast(holy_tree);
	free_ready_tokens_list(parser->postfix_note);
	free_token_list(tokens);
	free(parser);
	free(lexer);
	return (0);
}
