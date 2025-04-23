/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:57:52 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/23 14:53:27 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/structs.h"
#include <string.h>

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

const char  *token_type_name(t_token_type type)
{
    static const char   *names[] = {[TOKEN_WORD] = "WORD",
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
	while (current)
	{
		printf("[%d] Type: %s%s%s\n", index++,
			current->type == CMD ? GREEN : YELLOW,
			current->type == CMD ? "COMMAND" : "OPERATOR",
			RESET);
		if (current->type == CMD)
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
					printf("%s%s%s", CYAN, cmd->args[i], RESET);
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
					printf("    %s%s%s %s%s%s\n", MAGENTA, redir_str, RESET,
						BLUE, redir->file_or_limiter, RESET);
					redir = redir->next;
				}
			}
		}
		else if (current->type == OP)
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
}

/**
 * Enhanced AST printer without depth tracking
 * Uses recursive string building approach for tree lines
 */

// ANSI color codes for better visualization
#define COLOR_RESET   "\x1B[0m"
#define COLOR_RED     "\x1B[31m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_YELLOW  "\x1B[33m"
#define COLOR_BLUE    "\x1B[34m"
#define COLOR_MAGENTA "\x1B[35m"
#define COLOR_CYAN    "\x1B[36m"
#define COLOR_WHITE   "\x1B[37m"

char *get_op_string(int op_type) {
    switch (op_type) {
        case OP_PIPE:    return "PIPE (|)";
        case OP_AND:     return "AND (&&)";
        case OP_OR:      return "OR (||)";
        case OP_PAREN_L: return "LEFT_PAREN (()";
        case OP_PAREN_R: return "RIGHT_PAREN ())";
        default:         return "UNKNOWN";
    }
}

/**
 * Prints the AST recursively using a prefix string to track the tree structure
 * @param root The current node in the AST
 * @param prefix The string prefix to use for the current line
 * @param is_left Whether this node is a left child
 * @param is_last Whether this node is the last child of its parent
 */
void print_ast_node(t_ast *root, const char *prefix, int is_left, int is_last) {
    char next_prefix[1024];
    
    (void)is_left;
    // Print the current node
    printf("%s", prefix);
    
    if (is_last) {
        printf("└── ");
        sprintf(next_prefix, "%s    ", prefix);
    } else {
        printf("├── ");
        sprintf(next_prefix, "%s│   ", prefix);
    }
    
    // Handle NULL root
    if (root == NULL) {
        printf("%sNULL%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    
    // Print node information
    if (root->node == NULL) {
        printf("%sEMPTY NODE%s\n", COLOR_YELLOW, COLOR_RESET);
    } else {
        switch (root->node->type) {
            case CMD: {
                t_cmd *cmd = (t_cmd *)root->node->p_token;
                printf("%sCOMMAND:%s ", COLOR_GREEN, COLOR_RESET);
                
                if (cmd && cmd->cmd) {
                    printf("%s'%s'%s", COLOR_CYAN, cmd->cmd, COLOR_RESET);
                    
                    // Print command arguments if available
                    if (cmd->args && cmd->args[0]) {
                        printf(" with args: ");
                        for (int i = 0; cmd->args[i]; i++) {
                            printf("%s'%s'%s ", COLOR_CYAN, cmd->args[i], COLOR_RESET);
                        }
                    }
                } else {
                    printf("%s(null)%s", COLOR_RED, COLOR_RESET);
                }
                printf("\n");
                break;
            }
            case OP: {
                t_op *op = (t_op *)root->node->p_token;
                printf("%sOPERATOR:%s %s%s%s\n", 
                       COLOR_MAGENTA, COLOR_RESET,
                       COLOR_BLUE, get_op_string(op->type), COLOR_RESET);
                break;
            }
            default:
                printf("%sUNKNOWN TYPE: %d%s\n", 
                       COLOR_RED, root->node->type, COLOR_RESET);
                break;
        }
    }
    
    // Print left child if it exists
    if (root->left) {
        print_ast_node(root->left, next_prefix, 1, root->right == NULL);
    }
    
    // Print right child if it exists
    if (root->right) {
        print_ast_node(root->right, next_prefix, 0, 1);
    }
}

/**
 * Count nodes and find maximum depth of the tree
 */
void get_tree_stats(t_ast *root, int *nodes, int *depth, int current_depth) {
    if (root == NULL)
        return;
        
    (*nodes)++;
    if (current_depth > *depth)
        *depth = current_depth;
        
    get_tree_stats(root->left, nodes, depth, current_depth + 1);
    get_tree_stats(root->right, nodes, depth, current_depth + 1);
}

/**
 * Main function to print the AST
 */
void print_ast(t_ast *root) {
    int total_nodes = 0;
    int max_depth = 0;
    
    // Calculate tree statistics
    get_tree_stats(root, &total_nodes, &max_depth, 0);
    
    printf("%s========== ABSTRACT SYNTAX TREE ==========%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("Total nodes: %d, Maximum depth: %d\n\n", total_nodes, max_depth);
    
    if (root == NULL) {
        printf("%sEmpty tree (NULL root)%s\n", COLOR_RED, COLOR_RESET);
        return;
    }
    
    // Print the tree starting with an empty prefix
    print_ast_node(root, "", 0, 1);
    printf("%s==========================================%s\n", COLOR_YELLOW, COLOR_RESET);
}

/**
 * Simple version without colors for file output
 */
void print_ast_simple(t_ast *root) {
    // Call tree printing function with no prefix
    printf("Abstract Syntax Tree:\n");
    print_ast_node(root, "", 0, 1);
}