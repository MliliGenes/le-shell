/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/22 02:18:29 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

int	get_op_precedence(t_ready_token *token)
{
	t_op_type	op_type;

	op_type = ((t_op *)token->p_token)->type;
	if (op_type == OP_AND)
		return (2);
	else if (op_type == OP_OR)
		return (1);
	else if (op_type == OP_PIPE)
		return (3);
	else if (op_type == OP_PAREN_L || op_type == OP_PAREN_R)
		return (0);
	return (-1);
}

void	add_front_ops_stack(t_ready_token **head, t_ready_token *node)
{
	if (!head || !node)
		return ;
	node->prev = NULL;
	node->next = *head;
	if (*head)
		(*head)->prev = node;
	*head = node;
}

void	push_to_postfix(t_ready_token **head, t_ready_token *node)
{
	node->next = NULL;
	node->prev = NULL;
	add_back_ready_token(head, node);
}

t_ready_token	*pop_infix_note(t_parser *parser)
{
	t_ready_token	*popped_node;

	if (!parser || !parser->infix_note)
		return (NULL);
	popped_node = parser->infix_note;
	parser->infix_note = parser->infix_note->next;
	if (parser->infix_note)
		parser->infix_note->prev = NULL;
	popped_node->next = NULL;
	return (popped_node);
}

t_ready_token	*pop_op_stack_note(t_parser *parser)
{
	t_ready_token	*popped_node;

	if (!parser || !parser->ops_stack)
		return (NULL);
	popped_node = parser->ops_stack;
	parser->ops_stack = parser->ops_stack->next;
	if (parser->ops_stack)
		parser->ops_stack->prev = NULL;
	popped_node->next = NULL;
	return (popped_node);
}

void	op_to_postfix(t_ready_token *op, t_parser *parser)
{
	if (((t_op *)op->p_token)->type == OP_PAREN_L)
	{
		add_front_ops_stack(&parser->ops_stack, op);
		return ;
	}
	if (((t_op *)op->p_token)->type == OP_PAREN_R)
	{
		free_ready_tokens_list(op);
		while (parser->ops_stack
			&& ((t_op *)parser->ops_stack->p_token)->type != OP_PAREN_L)
			push_to_postfix(&parser->postfix_note, pop_op_stack_note(parser));
		if (parser->ops_stack)
			free_ready_tokens_list(pop_op_stack_note(parser));
		return ;
	}
	while (parser->ops_stack
		&& get_op_precedence(parser->ops_stack) >= get_op_precedence(op))
		push_to_postfix(&parser->postfix_note, pop_op_stack_note(parser));
	add_front_ops_stack(&parser->ops_stack, op);
}

void	shunting_yard(t_parser *parser)
{
	t_ready_token	*current_node;

	while (parser->infix_note)
	{
		current_node = pop_infix_note(parser);
		if (current_node->type == CMD)
			push_to_postfix(&parser->postfix_note, current_node);
		else if (current_node->type == OP)
			op_to_postfix(current_node, parser);
	}
	while (parser->ops_stack)
	{
		current_node = pop_op_stack_note(parser);
		if (((t_op *)current_node->p_token)->type != OP_PAREN_L)
			push_to_postfix(&parser->postfix_note, current_node);
	}
}

bool	check_input(char *input)
{
	return (check_quotes_balance(input) || check_parenthesis_balance(input)
		|| check_m_percent(input));
}

void	ll(void)
{
	system("leaks parser");
}

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->infix_note = NULL;
	parser->postfix_note = NULL;
	parser->ops_stack = NULL;
	return (parser);
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

# ifndef TEST
#  define TEST "( command1 < input1 > output1 ) || ( command2 < input2 2> error2 | command3 > output3 ) && command4 >> append_output < input4 | ( command5 > output5 2>> append_error )"
// #  define TEST "( ls *.c > \"testing\"'$the'test\"\"\"\"'''''''''''''''' -e | \"$grep\" \"$txt\" > \"text_files\" ) && ( cat < Makefile-e) && echo \"Text files found\"&& cat text_files.list|| (echo \"$No text files found\" >> error.log && exit 1) | wc -l < input.txt >> results.log"
# endif

t_ast	*ast_recursive(t_ready_token **postfix_tail)
{
	t_ready_token	*current;
	t_ast			*wrapper;

	current = *postfix_tail;
	if (!current)
		return (NULL);
	*postfix_tail = current->prev;
	wrapper = malloc(sizeof(t_ast));
	if (!wrapper)
		return (NULL);
	wrapper->node = current;
	wrapper->left = NULL;
	wrapper->right = NULL;
	if (current->type == OP)
	{
		wrapper->left = ast_recursive(postfix_tail);
		wrapper->right = ast_recursive(postfix_tail);
	}
	return (wrapper);
}

t_ast *post_to_tree(t_ready_token *postfix)
{
    while (postfix && postfix->next)
		postfix = postfix->next;
    return ast_recursive(&postfix);
}

void print_indentation(int level) {
    for (int i = 0; i < level * 4; i++) {
        printf(" ");
    }
}

void print_ast_readable_recursive(t_ast *root, int level) {
    if (root == NULL) {
        print_indentation(level);
        printf("└── NULL\n");
        return;
    }

    print_indentation(level);
    printf("└── ");

    if (root->node != NULL) {
        switch (root->node->type) {
            case CMD: {
                t_cmd *cmd = (t_cmd *)root->node->p_token;
                printf("Type: CMD, Value: %s\n", cmd && cmd->cmd ? cmd->cmd : "(null)");
                print_indentation(level + 1);
                printf("├── Left:\n");
                print_ast_readable_recursive(root->left, level + 2);
                print_indentation(level + 1);
                printf("└── Right:\n");
                print_ast_readable_recursive(root->right, level + 2);
                break;
            }
            case OP: {
                t_op *op = (t_op *)root->node->p_token;
                const char *op_str;
                switch (op->type) {
                    case OP_PIPE:
                        op_str = "|";
                        break;
                    case OP_AND:
                        op_str = "&&";
                        break;
                    case OP_OR:
                        op_str = "||";
                        break;
                    case OP_PAREN_L:
                        op_str = "(";
                        break;
                    case OP_PAREN_R:
                        op_str = ")";
                        break;
                    default:
                        op_str = "UNKNOWN";
                        break;
                }
                printf("Type: OP, Value: %s\n", op_str);
                print_indentation(level + 1);
                printf("├── Left:\n");
                print_ast_readable_recursive(root->left, level + 2);
                print_indentation(level + 1);
                printf("└── Right:\n");
                print_ast_readable_recursive(root->right, level + 2);
                break;
            }
            default:
                printf("Type: UNKNOWN\n");
                print_indentation(level + 1);
                printf("├── Left:\n");
                print_ast_readable_recursive(root->left, level + 2);
                print_indentation(level + 1);
                printf("└── Right:\n");
                print_ast_readable_recursive(root->right, level + 2);
                break;
        }
    } else {
        printf("Type: NULL\n");
        print_indentation(level + 1);
        printf("├── Left:\n");
        print_ast_readable_recursive(root->left, level + 2);
        print_indentation(level + 1);
        printf("└── Right:\n");
        print_ast_readable_recursive(root->right, level + 2);
    }
}

void print_ast(t_ast *root) {
    printf("Abstract Syntax Tree:\n");
    print_ast_readable_recursive(root, 0);
}

void free_ast(t_ast *root)
{
	if (!root)
		return;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
}

int	main(void)
{
	t_lexer		*lexer;
	t_token		*tokens;
	
	t_parser	*parser;
	t_ast		*holy_tree;

	if (check_input(TEST))
		return (1);
	lexer = NULL;
	tokens = NULL;
	parser = NULL;
	holy_tree = NULL;
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (!tokens->value || validate_tokens(tokens))
		return (free(lexer), free_token_list(tokens), 1);
	classify_tokens(tokens);
	parser = init_parser();
	if (!parser)
		return (free(lexer), free_token_list(tokens), 1);
	extract_tokens(tokens, &parser->infix_note);
	print_notation(parser->infix_note);
	shunting_yard(parser);
	print_notation(parser->postfix_note);
	holy_tree = post_to_tree(parser->postfix_note);
	print_ast(holy_tree);
	free_ast(holy_tree);
	free_ready_tokens_list(parser->postfix_note);
	free_token_list(tokens);
	free(parser);
	free(lexer);
	return (0);
}
