/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/03/21 07:53:07 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// Token types for lexical analysis
typedef enum e_token_type
{
	TOKEN_WORD,      // Commands and arguments
	TOKEN_PIPE,      // |
	TOKEN_REDIR_IN,  // <
	TOKEN_REDIR_OUT, // >
	TOKEN_APPEND,    // >>
	TOKEN_HEREDOC,   // <<
	TOKEN_AND,       // && (bonus)
	TOKEN_OR,        // || (bonus)
	TOKEN_L_PAREN,   // ( (bonus)
	TOKEN_R_PAREN,   // ) (bonus)
	TOKEN_EOF        // End of input
}						t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

// AST node types
typedef enum e_node_type
{
	NODE_COMMAND, // Simple command with args
	NODE_PIPE,    // Pipe operator
	NODE_REDIR,   // Redirection
	NODE_AND,     // AND operator (bonus)
	NODE_OR,      // OR operator (bonus)
}						t_node_type;

// AST node structure
typedef struct s_ast_node
{
	t_node_type			type;

	// For command nodes
	char **args; // Command and its arguments

	// For redirection nodes
	int redir_type; // <, >, >>, <<
	char *file;     // Filename or delimiter

	// Tree structure
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

// Environment variable structure
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

// Main shell structure
typedef struct s_shell
{
	t_token *tokens;     // Linked list of tokens
	t_ast_node *ast;     // Abstract Syntax Tree root
	t_env *env;          // Environment variables
	int last_exit_code;  // $? value
	int signal_received; // Global for signal handling
}						t_shell;

#endif