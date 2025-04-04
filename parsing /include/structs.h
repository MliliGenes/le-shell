/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/04 19:17:56 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

/**
 * enum e_token_type - Types of tokens in lexical analysis
 *
 * @TOKEN_WORD: Regular command word or argument
 * @TOKEN_PIPE: Pipe character '|'
 * @TOKEN_REDIR_IN: Input redirection '<'
 * @TOKEN_REDIR_OUT: Output redirection '>'
 * @TOKEN_APPEND: Append redirection '>>'
 * @TOKEN_HEREDOC: Here document '<<'
 * @TOKEN_AND: Logical AND '&&'
 * @TOKEN_OR: Logical OR '||'
 * @TOKEN_PAREN_L: Left parenthesis '('
 * @TOKEN_PAREN_R: Right parenthesis ')'
 * @TOKEN_EOF: End of input marker
 */
typedef enum e_token_type
{
	TOKEN_WORD,      
    // TOKEN_S_QUOTE,    
    // TOKEN_D_QUOTE,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_L,
	TOKEN_PAREN_R,
	TOKEN_EOF
}						t_token_type;

/**
 * struct s_token - Token structure for lexical analysis
 *
 * @value: String value of the token
 * @type: Type of the token from e_token_type
 * @next: Pointer to next token in linked list
 */
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	int					n_index;
	bool				join;
	struct s_token		*next;
}						t_token;

/**
 * struct s_lexer - Lexer state structure
 *
 * @input: Input string being processed
 * @pos: Current position in input string
 */
typedef struct s_lexer
{
	char				*input;
	int					len;
	int					pos;
	char				current_char;
}						t_lexer;

/**
 * enum e_redir_type - Types of redirection operations
 *
 * @REDIR_IN: Input redirection '<'
 * @REDIR_OUT: Output redirection '>'
 * @REDIR_APPEND: Append redirection '>>'
 * @REDIR_HEREDOC: Here document '<<'
 */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redir_type;

/**
 * struct s_redir - Redirection operation structure
 *
 * @type: Type of redirection from e_redir_type
 * @file: Target filename or heredoc delimiter
 * @next: Pointer to next redirection in list
 */
typedef struct s_redir
{
	t_redir_type		type;
	char				*file_or_limiter;
	struct s_redir		*next;
}						t_redir;

/**
 * struct s_cmd - Simple command structure
 *
 * @args: Array of command arguments (NULL-terminated)
 * @redirs: List of redirections for this command
 * @next: Pointer to next command in pipeline or list
 */
typedef struct s_cmd
{
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}						t_cmd;

/**
 * enum e_op_type - Types of AST node operations
 *
 * @OP_PIPE: Pipe operation '|'
 * @OP_AND: Logical AND '&&'
 * @OP_OR: Logical OR '||'
 */
typedef enum e_op_type
{
	OP_PIPE,
	OP_AND,
	OP_OR
}						t_op_type;

/**
 * struct s_ast - Abstract Syntax Tree node structure
 *
 * @type: Node type (AST_CMD, AST_PIPE, AST_AND_OR, AST_SUBSHELL)
 * @cmd: Command node (valid when type == AST_CMD)
 * @left: Left child node (valid for PIPE/AND_OR nodes)
 * @right: Right child node (valid for PIPE/AND_OR nodes)
 * @op: Operation type (valid for PIPE/AND_OR nodes)
 * @subshell: Subshell node (valid when type == AST_SUBSHELL)
 * @redirs: Redirections that apply to this entire node
 */
typedef struct s_ast
{
	enum
	{
		AST_CMD,
		AST_PIPE,
		AST_AND_OR,
		AST_SUBSHELL
	} type;

	t_cmd				*cmd;
	struct s_ast		*left;
	struct s_ast		*right;
	t_op_type			op;
	struct s_ast		*subshell;
	t_redir				*redirs;
}						t_ast;

/**
 * struct s_env_var - Environment variable entry
 *
 * @key: Variable name
 * @value: Variable value
 * @next: Pointer to next environment variable
 */
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

/**
 * struct s_shell - Shell global state structure
 *
 * @env: Linked list of environment variables
 * @last_status: Exit status of last executed command
 * @path: Array of paths from PATH environment variable
 * @ast: Abstract Syntax Tree of current input
 * @running: Flag indicating if shell should continue running
 */
typedef struct s_shell
{
	t_env_var			*env;
	int					last_status;
	char				**path;
	t_ast				*ast;
	int					running;
}						t_shell;

#endif