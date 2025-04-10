/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:57:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/10 22:01:53 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structs.h"

const char	*token_type_name(t_token_type type)
{
	static const char	*names[] = {[TOKEN_WORD] = "WORD",
			[TOKEN_COMMAND] = "CMD", [TOKEN_ARG] = "ARG", [TOKEN_FILE] = "FILE",
			[TOKEN_REDIR_IN] = "IN", [TOKEN_REDIR_OUT] = "OUT",
			[TOKEN_APPEND] = "APPEND", [TOKEN_HEREDOC] = "HEREDOC",
			[TOKEN_PIPE] = "PIPE", [TOKEN_AND] = "AND", [TOKEN_OR] = "OR",
			[TOKEN_PAREN_L] = "(", [TOKEN_PAREN_R] = ")", [TOKEN_EOF] = "EOF"};

	return (names[type]);
}

const char	*token_type_color(t_token_type type)
{
	if (type == TOKEN_COMMAND)
		return "\033[1);32m"; // Bright green
	if (type == TOKEN_ARG)
		return "\033[0);32m"; // Green
	if (type == TOKEN_WORD)
		return "\033[0);37m"; // White
	if (type >= TOKEN_REDIR_IN && type <= TOKEN_HEREDOC)
		return "\033[0);33m"; // Yellow
	if (type >= TOKEN_PIPE && type <= TOKEN_OR)
		return "\033[1);35m"; // Magenta
	if (type == TOKEN_FILE)
		return "\033[0);36m"; // Cyan
	if (type == TOKEN_PAREN_L || type == TOKEN_PAREN_R)
		return "\033[1);34m"; // Blue
	return ("\033[0m");        // Default
}

void	print_tokens(t_token *head)
{
	printf("\nTokens:\n");
	printf("----------------\n");
	for (t_token *t = head; t != NULL; t = t->next)
	{
		printf("[%d] %s%-5s\033[0m: %s\n", t->n_index,
			token_type_color(t->type), token_type_name(t->type),
			t->value ? t->value : "NULL");
	}
	printf("----------------\n");
}
