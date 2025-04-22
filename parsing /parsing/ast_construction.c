/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:16:18 by le-saad           #+#    #+#             */
/*   Updated: 2025/04/22 12:38:22 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

t_ast	*ast_recursive(t_ready_token **postfix_tail)
{
	t_ready_token	*current;
	t_ast			*wrapper;

	current = *postfix_tail;
	if (!current)
		return (NULL);
	*postfix_tail = current->prev;
	wrapper = malloc(sizeof(t_ast));
	if (!wrapper)
		return (NULL);
	wrapper->node = current;
	wrapper->right = NULL;
	wrapper->left = NULL;
	if (current->type == OP)
	{
		wrapper->right = ast_recursive(postfix_tail);
		wrapper->left = ast_recursive(postfix_tail);
	}
	return (wrapper);
}

t_ast	*post_to_tree(t_ready_token *postfix)
{
	while (postfix && postfix->next)
		postfix = postfix->next;
	return (ast_recursive(&postfix));
}
