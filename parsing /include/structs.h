/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/01 22:35:34 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

typedef enum e_token_type
{
	TOKEN_WORD,
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
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

typedef struct s_lexer
{
	char					*input;
	int						pos;
}							t_lexer;

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
	char					*file;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd
{
	char					**args;
	t_redir					*redirs;
	struct s_cmd			*next;
}							t_cmd;

typedef enum e_op_type
{
	OP_PIPE,
	OP_AND,
	OP_OR
}							t_op_type;

typedef struct s_ast
{
    enum {
        AST_CMD,
        AST_PIPE,
        AST_AND_OR,
        AST_SUBSHELL
    } type;

    t_cmd *cmd;

    struct s_ast *left;
    struct s_ast *right;
    t_op_type op;

    struct s_ast *subshell;

    t_redir *redirs;
} t_ast;

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