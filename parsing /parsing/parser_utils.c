/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:16:26 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 12:37:37 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

bool	check_input(char *input)
{
	return (check_quotes_balance(input) || check_parenthesis_balance(input)
		|| check_m_percent(input));
}
