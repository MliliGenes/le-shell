/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:57:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/12 21:13:46 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structs.h"

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLDWHITE   "\033[1m\033[37m"

const char *token_color(t_token_type type)
{
	static const char *colors[] = {
		[TOKEN_WORD] = WHITE,
		[TOKEN_COMMAND] = GREEN,
		[TOKEN_ARG] = CYAN,
		[TOKEN_FILE] = BLUE,
		[TOKEN_REDIR_IN] = MAGENTA,
		[TOKEN_REDIR_OUT] = MAGENTA,
		[TOKEN_APPEND] = MAGENTA,
		[TOKEN_HEREDOC] = MAGENTA,
		[TOKEN_PIPE] = YELLOW,
		[TOKEN_AND] = YELLOW,
		[TOKEN_OR] = YELLOW,
		[TOKEN_PAREN_L] = RED,
		[TOKEN_PAREN_R] = RED,
		[TOKEN_EOF] = BOLDWHITE
	};
	return (colors[type]);
}

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
	printf("\n%sTokens:\n", BOLDWHITE);
	printf("----------------%s\n", RESET);
	for (t_token *t = head; t != NULL; t = t->next)
	{
		const char *color = token_color(t->type);
		printf("[%02d] %s%s%s:\t%s\n", t->n_index,
				color, token_type_name(t->type), RESET,
				t->value ? t->value : "NULL");
	}
	printf("%s----------------\n%s", BOLDWHITE, RESET);
}
