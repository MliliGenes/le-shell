/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/01 22:24:28 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

/**
 * @brief Token types for lexical analysis
 */
typedef enum e_token_type
{
	TOKEN_WORD,      /* Command or argument */
	TOKEN_PIPE,      /* Pipe operator (|) */
	TOKEN_REDIR_IN,  /* Input redirection (<) */
	TOKEN_REDIR_OUT, /* Output redirection (>) */
	TOKEN_APPEND,    /* Append redirection (>>) */
	TOKEN_HEREDOC,   /* Here document (<<) */
	TOKEN_AND,       /* Logical AND (&&) for bonus */
	TOKEN_OR,        /* Logical OR (||) for bonus */
	TOKEN_PAREN_L,   /* Left parenthesis for bonus */
	TOKEN_PAREN_R,   /* Right parenthesis for bonus */
	TOKEN_EOF        /* End of input */
}	t_token_type;

/**
 * @brief Token structure
 * @details Basic unit after lexical analysis
 */
typedef struct s_token
{
	char			*value;  /* Token string value */
	t_token_type	type;    /* Type of the token */
	struct s_token	*next;   /* Next token in list */
}	t_token;

/**
 * @brief Lexer for tokenizing input
 */
typedef struct s_lexer
{
	char	*input;     /* Input string */
	int		pos;        /* Current position */
}	t_lexer;

/**
 * @brief Redirection types
 */
typedef enum e_redir_type
{
	REDIR_IN,      /* Input (<) */
	REDIR_OUT,     /* Output (>) */
	REDIR_APPEND,  /* Append (>>) */
	REDIR_HEREDOC  /* Here document (<<) */
}	t_redir_type;

/**
 * @brief Redirection structure
 */
typedef struct s_redir
{
	t_redir_type	type;      /* Type of redirection */
	char			*file;      /* Filename or delimiter */
	struct s_redir	*next;      /* Next redirection */
}	t_redir;

/**
 * @brief Simple command structure
 */
typedef struct s_cmd
{
	char			**args;    /* Command and its arguments */
	t_redir			*redirs;   /* List of redirections */
	struct s_cmd	*next;     /* For simple command lists */
}	t_cmd;

/**
 * @brief Operator types (for bonus part)
 */
typedef enum e_op_type
{
	OP_PIPE,  /* Pipe (|) */
	OP_AND,   /* Logical AND (&&) */
	OP_OR     /* Logical OR (||) */
}	t_op_type;

/**
 * @brief AST node structure
 * @details Represents commands, pipes, and logical operators
 */
typedef struct s_ast
{
	enum {
		AST_CMD,     /* Simple command */
		AST_PIPE,    /* Pipeline */
		AST_AND_OR,  /* Logical operator (&&, ||) */
		AST_SUBSHELL /* Group in parentheses (bonus) */
	} type;
	
	union {
		t_cmd *cmd;                 /* For AST_CMD */
		struct {
			struct s_ast	*left;
			struct s_ast	*right;
			t_op_type		op;
		} binary;                   /* For AST_PIPE and AST_AND_OR */
		struct s_ast *subshell;     /* For AST_SUBSHELL */
	} content;
	
	t_redir *redirs;               /* Redirections at this level */
}	t_ast;

/**
 * @brief Environment variable structure
 */
typedef struct s_env_var
{
	char				*key;     /* Variable name */
	char				*value;   /* Variable value */
	struct s_env_var	*next;    /* Next variable */
}	t_env_var;

/**
 * @brief Shell state structure
 */
typedef struct s_shell
{
	t_env_var	*env;          /* Environment variables */
	int			last_status;   /* Exit status of last command ($?) */
	char		**path;        /* PATH directories for command lookup */
	t_ast		*ast;          /* Abstract syntax tree of current command */
	int			running;       /* Shell running status */
}	t_shell;

#endif