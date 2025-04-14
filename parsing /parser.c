/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/14 02:45:37 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

t_redir	*create_redir_node(t_redir_type type, char *file_or_limiter)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir || !file_or_limiter)
		return (NULL);
	redir->type = type;
	redir->file_or_limiter = file_or_limiter;
	redir->next = NULL;
	return (redir);
}

void	add_back_redir_node(t_redir **head, t_redir *node)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_cmd	*create_cmd_node(char **args, t_redir *redirs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd || !args || !*args || !redirs)
		return (NULL);
	cmd->args = args;
	cmd->cmd = args[0];
	cmd->redirs = redirs;
	cmd->fds[0] = -1;
	cmd->fds[1] = -1;
	return (cmd);
}

t_op	*create_op_node(t_op_type type)
{
	t_op	*op;

	op = malloc(sizeof(t_cmd));
	if (!op)
		return (NULL);
	op->type = type;
	return (op);
}

t_ready_token	*create_ready_token_node(void *token, int type)
{
	t_ready_token	*r_token;

	r_token = malloc(sizeof(t_ready_token));
	if (!r_token || !token)
		return (NULL);
	r_token->p_token = token;
	r_token->type = type;
	r_token->next = NULL;
	r_token->prev = NULL;
	return (r_token);
}

void	add_back_ready_token(t_ready_token **head, t_ready_token *node)
{
	t_ready_token	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

int	types_mapper(t_token_type type)
{
	if (type == TOKEN_PAREN_L)
		return (OP_PAREN_L);
	if (type == TOKEN_PAREN_R)
		return (OP_PAREN_R);
	if (type == TOKEN_PIPE)
		return (OP_PIPE);
	if (type == TOKEN_AND)
		return (OP_AND);
	if (type == TOKEN_OR)
		return (OP_OR);
	return (-1);
}

t_cmd	*handle_cmd(t_token *head)
{
	static int	last_index;
	int			size;
	t_cmd		*cmd;

	while (head->prev)
	{
		head = head->prev;
	}
	last_index = head->n_index;
	return cmd;
}

bool	ready_tokens_list(t_token *tokens, t_ready_token **head)
{
	t_op			*tmp_op;
	t_cmd			*tmp_cmd;
	t_ready_token	*tmp_token;

	while (tokens->type != TOKEN_EOF)
	{
		if (is_paren(tokens->type))
		{
			tmp_op = create_op_node(types_mapper(tokens->type));
			if (!tmp_op)
				return (false);
			tmp_token = create_ready_token_node(tmp_op, P_TOKEN_OP);
			if (!tmp_token)
				return (false);
			add_back_ready_token(head, tmp_token);
		}
		if (is_op(tokens->type))
		{
			// TODO go back and pick up cmd args and redirs handle_cmd(tokens);
			// TODO add it back and add
			// TODO add back the op
		}
		tokens = tokens->next;
	}
	return (true);
}

void	ll(void)
{
	system("leaks parser");
}

int	main(void)
{
	t_lexer	*lexer;
	t_token	*tokens;

	// t_ready_token	*ready_tokens;
	atexit(ll);
	if (check_quotes_balance(TEST) || check_parenthesis_balance(TEST)
		|| check_m_percent(TEST))
		return (1);
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &tokens);
	if (validate_tokens(tokens))
		return (1);
	classify_tokens(tokens);
	// TODO: trim_cmds_quotes();
	print_tokens(tokens);
	free_token_list(tokens);
	free(lexer);
	return (0);
}
