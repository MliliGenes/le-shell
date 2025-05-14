/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:22:09 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:22:16 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

t_entry	*create_entry(char *value)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->value = strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->entry_len = strlen(new->value);
	new->next = NULL;
	return (new);
}

void	free_entry(t_entry *entry)
{
	if (!entry)
		return ;
	free(entry->value);
	free(entry);
}

void	free_entry_list(t_entry *head)
{
	t_entry *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_entry(tmp);
	}
}