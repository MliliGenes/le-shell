/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/23 17:14:43 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLDWHITE "\033[1m\033[37m"

# define REDIR_NEEDS_TARGET "Redirection needs target file"
# define CONSECUTIVE_OPS "Consecutive operators not allowed"
# define CHAINED_REDIRS "Can't chain redirections"
# define INVALID_AFTER_PAREN "Invalid token after parenthesis"
# define INVALID_SEQUENCE "Invalid token sequence"
# define MISPLACED_PAREN "Misplaced parenthesis"
# define PIPE_CONNECT "Pipe must connect commands"

typedef struct s_lexer
{
	char					*input;
	int						len;
	int						pos;
	char					current_char;
}							t_lexer;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_FILE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PL,
	TOKEN_PR,
	TOKEN_EOF
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	int						n_index;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redir
{
	t_redir_type			type;
	char					*file_or_limiter;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
	char					**args;
	char					*cmd;
	int						fds[2];
	t_redir					*redirs;
}							t_cmd;

typedef enum e_op_type
{
	OP_PAREN_L,
	OP_PAREN_R,
	OP_PIPE,
	OP_AND,
	OP_OR
}							t_op_type;

typedef struct s_op
{
	t_op_type				type;
}							t_op;

typedef enum e_ready_token_type
{
	CMD,
	OP,
}							t_ready_token_type;

typedef struct s_ready_token
{
	t_ready_token_type		type;
	void					*p_token;
	struct s_ready_token	*next;
	struct s_ready_token	*prev;
}							t_ready_token;

typedef struct s_ast
{
	t_ready_token			*node;
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast;

typedef struct s_parser
{
	t_ready_token			*infix_note;
	t_ready_token			*ops_stack;
	t_ready_token			*postfix_note;
	t_ast					*holy_tree;
}							t_parser;

typedef struct s_env_var
{
	char					*key;
	char					*value;
	struct s_env_var		*next;
}							t_env_var;

typedef struct s_shell
{
	t_env_var				*env;
	int						last_status;
	char					**path;
	t_ast					*ast;
	int						running;
}							t_shell;

#endif