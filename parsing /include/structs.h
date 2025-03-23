/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:20:05 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/03/23 08:00:27 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}					t_redir_type;

typedef struct s_redir_token
{
	char			*file_name;
	t_redir_type	type;
}					t_redir_token;

typedef struct s_cmd_node
{
	char			*cmd;
	char			*args;
	t_redir_token	*redir;
}					t_cmd_node;

typedef struct s_op_node
{
	char			*cmd;
	char			*args;
	t_redir_token	*redir;
}					t_op_node;

typedef enum s_token_type
{
	CMD_TOKEN,
	OP_TOKEN,
	L_PAREN_TOKEN,
    R_PAREN_TOKEN,
}					t_token_type;

typedef struct s_list
{
	void			*token;
	t_token_type	token_type;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

#endif