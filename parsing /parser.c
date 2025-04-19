/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/19 01:49:01 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks parser");
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
	// t_parser	*parser = malloc(sizeof(t_parser));
	// parser->cmds_stack = NULL;
	// parser->ops_stack = NULL;
	
	atexit(ll);
	lexer = NULL;
	tokens = NULL;
	ready_tokens = NULL;
	if (check_balance(TEST))	
		return (1);
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), 1);
	classify_tokens(tokens);
	print_tokens(tokens);
	trim_quotes(tokens); 
	print_tokens(tokens);
	extract_tokens(tokens, &ready_tokens);
	print_ready_tokens(ready_tokens);
	free_ready_tokens_list(ready_tokens);
	free(lexer);
	return (0);
}
