/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/14 00:38:03 by sel-mlil         ###   ########.fr       */
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

t_ready_token	*create_ready_token(void *token, int type)
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

void

	void
	ll(void)
{
	system("leaks parser");
}

int	main(void)
{
	t_lexer			*lexer;
	t_token			*head;
	t_ready_token	*ready;

	atexit(ll);
	head = NULL;
	ready = NULL;
	if (check_quotes_balance(TEST) || check_parenthesis_balance(TEST)
		|| check_m_percent(TEST))
		return (1);
	lexer = init_lexer(TEST);
	if (!lexer)
		return (1);
	create_tokens_list(lexer, &head);
	if (validate_tokens(head))
		return (1);
	classify_tokens(head);
	// TODO: trim_cmds_quotes();
	print_tokens(head);
	free_token_list(head);
	free(lexer);
	return (0);
}
