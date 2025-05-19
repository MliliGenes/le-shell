/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:22:09 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/19 16:51:47 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char *_mark_astrestisk(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			str[i] = 3;
		i++;
	}
	return (str);
}

t_entry	*create_entry(char *value)
{
	t_entry	*new;
	char *tmp;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	tmp = _mark_astrestisk(value);
	new->value = strdup(tmp);
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
	t_entry	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_entry(tmp);
	}
}
