/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/16 20:19:19 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"



void	ll(void)
{
	system("leaks parser");
}

int	main(void)
{
	t_lexer			*lexer;
	t_token			*tokens;
	t_ready_token	*ready_tokens;

	atexit(ll);
	tokens = NULL;
	ready_tokens = NULL;
	if (check_quotes_balance(TEST) || check_parenthesis_balance(TEST)
		|| check_m_percent(TEST))
		return (1);
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (validate_tokens(tokens))
		return (1);
	classify_tokens(tokens);
	print_tokens(tokens);
	extract_tokens(tokens, &ready_tokens);
	print_ready_tokens(ready_tokens);
	free(lexer);
	return (0);
}
