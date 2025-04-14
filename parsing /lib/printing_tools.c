/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:57:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/14 23:54:26 by sel-mlil         ###   ########.fr       */
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
		[TOKEN_PL] = RED,
		[TOKEN_PR] = RED,
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
			[TOKEN_PL] = "OPEN", [TOKEN_PR] = "CLOSE", [TOKEN_EOF] = "EOF"};

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


void	print_ready_tokens(t_ready_token *head)
{
	t_ready_token	*current;
	int				index;
	t_cmd			*cmd;
	t_redir			*redir;
	char			*redir_str;
	t_op			*op;
	char			*op_str;

	current = head;
	index = 0;
	printf("\n%s--- Ready Tokens List ---%s\n", BOLDWHITE, RESET);
	while (current)
	{
		printf("[%d] Type: %s%s%s\n", index++,
			current->type == P_TOKEN_CMD ? GREEN : YELLOW,
			current->type == P_TOKEN_CMD ? "COMMAND" : "OPERATOR",
			RESET);
		if (current->type == P_TOKEN_CMD)
		{
			cmd = (t_cmd *)current->p_token;
			printf("  %sCommand%s: %s%s%s\n", GREEN, RESET, WHITE, 
				cmd->cmd ? cmd->cmd : "(null)", RESET);
			// Print arguments
			printf("  %sArguments%s: ", CYAN, RESET);
			if (cmd->args)
			{
				for (int i = 0; cmd->args[i]; i++)
				{
					printf("%s'%s'%s", CYAN, cmd->args[i], RESET);
					if (cmd->args[i + 1])
						printf(", ");
				}
			}
			else
			{
				printf("(none)");
			}
			printf("\n");
			// Print redirections
			printf("  %sRedirections%s:\n", MAGENTA, RESET);
			redir = cmd->redirs;
			if (!redir)
			{
				printf("    (none)\n");
			}
			else
			{
				while (redir)
				{
					if (redir->type == REDIR_IN)
						redir_str = "<";
					else if (redir->type == REDIR_OUT)
						redir_str = ">";
					else if (redir->type == REDIR_APPEND)
						redir_str = ">>";
					else
						redir_str = "<<";
					printf("    %s%s%s %s'%s'%s\n", MAGENTA, redir_str, RESET,
						BLUE, redir->file_or_limiter, RESET);
					redir = redir->next;
				}
			}
		}
		else if (current->type == P_TOKEN_OP)
		{
			op = (t_op *)current->p_token;
			if (op->type == OP_PIPE)
				op_str = "PIPE";
			else if (op->type == OP_AND)
				op_str = "AND";
			else if (op->type == OP_OR)
				op_str = "OR";
			else if (op->type == OP_PAREN_L)
				op_str = "LEFT PARENTHESIS";
			else if (op->type == OP_PAREN_R)
				op_str = "RIGHT PARENTHESIS";
			else
				op_str = "UNKNOWN";
			printf("  %sOperator%s: %s%s%s\n", YELLOW, RESET, YELLOW, op_str, RESET);
		}
		printf("\n");
		current = current->next;
	}
	printf("%s--- End of Ready Tokens ---%s\n\n", BOLDWHITE, RESET);
}
