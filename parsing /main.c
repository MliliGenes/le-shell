/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/24 18:30:12 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void    ll(void)
{
    system("leaks parser");
}

void    print_notation(t_ready_token *head)
{
    t_ready_token  *current;
    t_cmd         *cmd;
    t_op          *op;

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

int main(void)
{
    t_parser    *parser;
    char        *input;

    // atexit(ll);
    rl_bind_key('\t', rl_complete);
    while (1)
    {
        input = readline("le-shell> ");
        if (!input)
            break;
		if (!*input)
			continue;
        add_history(input);
        parser = parse_input(input);
        if (parser && parser->holy_tree)
        {
            print_ast(parser->holy_tree);
			print_ready_tokens(parser->postfix_note);
            free_ast(parser->holy_tree);
            free_ready_tokens_list(parser->postfix_note);
            free(parser);
        }
        free(input);     
    }
    return (0);
}
