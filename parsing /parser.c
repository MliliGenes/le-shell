/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/23 12:43:04 by sel-mlil         ###   ########.fr       */
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

// #ifndef TEST
// # define TEST "(ls -la || hghgdhg) && ls -la | grep hjhjh && (hi && hiii)"
// // #  define TEST "( ls *.c > \"testing\"'$the'test\"\"\"\"''''''''''''''''
// 	-e | \"$grep\" \"$txt\" > \"text_files\" ) && ( cat < Makefile-e)
// 	&& echo \"Text files found\"&& cat text_files.list|| (echo \"$No text files found\" >> error.log
// 	&& exit 1) | wc -l < input.txt >> results.log"
// #endif

int	main(void)
{
	t_parser	*parser;
	char		*input;

	atexit(ll);
	rl_bind_key('\t', rl_complete);
	while (1)
	{
		input = readline("le-shell> ");
		if (!input)
			break ;
		add_history(input);
		parser = parse_input(input);
		if (parser)
		{
			print_ast(parser->holy_tree);
			free_ast(parser->holy_tree);
			free_ready_tokens_list(parser->postfix_note);
			free(parser);
			free(input);
		}
	}
	return (0);
}
