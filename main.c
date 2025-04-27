/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/27 16:32:59 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks minishell");
}

int	main(void)
{
	t_parser	*parser;
	char		*input;

	atexit(ll);
	rl_bind_key('\t', rl_complete);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		parser = parse_input(input);
		if (parser && parser->holy_tree)
			print_ast_simple(parser->holy_tree);
		free_ast(parser->holy_tree);
		free_ready_tokens_list(parser->postfix_note);
		free(parser);
		free(input);
		input = NULL;
	}
	return (0);
}
