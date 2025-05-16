/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 04:56:00 by le-saad           #+#    #+#             */
/*   Updated: 2025/05/16 03:40:32 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	handle_and(t_ast *node, t_shell *shell)
{
	int	left_status;

	left_status = execute_ast_node(node->left, shell);
	if (left_status == 0)
	{
		return (execute_ast_node(node->right, shell));
	}
	return (left_status);
}

int	handle_or(t_ast *node, t_shell *shell)
{
	int	left_status;

	left_status = execute_ast_node(node->left, shell);
	if (left_status != 0)
	{
		return (execute_ast_node(node->right, shell));
	}
	return (left_status);
}
