/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/12 21:37:11 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks parser");
}

int	main(int ac, char **av, char **envp)
{
	t_lexer	*lexer;
	t_token	*head;

	// atexit(ll);
	(void)ac;
	(void)av;
	(void)envp;
	head = NULL;
	lexer = init_lexer(TEST);
	if (!lexer || check_quotes_balance(lexer->input)
		|| check_parenthesis_balance(lexer->input)
		|| check_m_percent(lexer->input))
		return (1);
	create_tokens_list(lexer, &head);
	if (validate_tokens(head))
		return (1);
	classify_tokens(head);
	print_tokens(head);
	free_token_list(head);
	free(lexer);
	return (0);
}
