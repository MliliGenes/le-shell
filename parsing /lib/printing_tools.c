/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:57:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/11 18:59:34 by sel-mlil         ###   ########.fr       */
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
			[TOKEN_PAREN_L] = "OPEN", [TOKEN_PAREN_R] = "CLOSE", [TOKEN_EOF] = "EOF"};

	return (names[type]);
}

void	print_tokens(t_token *head)
{
	printf("\nTokens:\n");
	printf("----------------\n");
	for (t_token *t = head; t != NULL; t = t->next)
	{
		printf("[%d] %-5s: %s\n", t->n_index,
			 token_type_name(t->type),
			t->value ? t->value : "NULL");
	}
	printf("----------------\n");
}
