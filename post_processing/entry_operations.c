/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:23:32 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 23:45:23 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	calculate_total_length(t_entry *head)
{
	int		total_len;
	int		entry_count;
	t_entry	*current;

	total_len = 0;
	entry_count = 0;
	current = head;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			total_len += current->entry_len;
			entry_count++;
		}
		current = current->next;
	}
	if (entry_count)
		total_len += (entry_count - 1);
	total_len += 1;
	return (total_len);
}

static void	copy_to_buffer(t_entry *head, char *result)
{
	int		position;
	int		is_first_entry;
	t_entry	*current;

	position = 0;
	is_first_entry = 1;
	current = head;
	while (current)
	{
		if (current->value)
		{
			if (!is_first_entry)
				result[position++] = ' ';
			strcpy(result + position, mark_space(current->value));
			position += current->entry_len;
			is_first_entry = 0;
		}
		current = current->next;
	}
	result[position] = '\0';
}

char	*join_entries(t_entry *head)
{
	if (!head)
		return (NULL);

	int total_len = calculate_total_length(head);
	char *result = malloc(total_len);
	if (!result)
		return (NULL);
	copy_to_buffer(head, result);
	return (result);
}
