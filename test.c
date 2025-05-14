/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:14:02 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:59:35 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"

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

void	free_entry_list(t_entry *head)
{
	t_entry	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	add_back_entry(t_entry **head, t_entry *new)
{
	t_entry	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_entry	*get_all_entries(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_entry			*head;
	t_entry			*new;

	head = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry)
	{
		new = create_entry(entry->d_name);
		if (!new)
			return (free_entry_list(head), NULL);
		add_back_entry(&head, new);
		entry = readdir(dir);
	}
	return (closedir(dir), head);
}

int	wildcardMatch(const char *input, const char *pattern)
{
	if (*pattern == '\0')
		return (*input == '\0');
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (*(pattern + 1) == '\0')
			return (1);
		while (*input != '\0')
		{
			if (wildcardMatch(input, pattern + 1))
				return (1);
			input++;
		}
		return (wildcardMatch(input, pattern + 1));
	}
	if (*input != '\0' && (*pattern == *input))
		return (wildcardMatch(input + 1, pattern + 1));
	return (0);
}

t_entry	*filter_entries_by_pattern(t_entry *old, const char *pattern)
{
	t_entry	*current;
	t_entry	*new_list;
	t_entry	*new_entry;

	current = old;
	new_list = NULL;
	while (current)
	{
		if (pattern[0] == '*' && *current->value == '.')
		{
			current = current->next;
		}
		else if (wildcardMatch(current->value, pattern))
		{
			new_entry = create_entry(current->value);
			if (!new_entry)
				return (NULL);
			add_back_entry(&new_list, new_entry);
		}
		current = current->next;
	}
	free_entry_list(old);
	return (new_list);
}

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
	total_len += (entry_count - 1);
	total_len += 1;
	return (total_len);
}

static void	copy_to_buffer(t_entry *head, char *result)
{
	t_entry	*current;
	int		position;
	int		is_first_entry;

	current = head;
	position = 0;
	is_first_entry = 1;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			if (!is_first_entry)
			{
				result[position] = ' ';
				position++;
			}
			strcpy(result + position, current->value);
			position += current->entry_len;
			is_first_entry = 0;
		}
		current = current->next;
	}
	result[position] = '\0';
}

char	*join_entries(t_entry *head)
{
	int		total_len;
	char	*result;

	if (head == NULL)
		return (NULL);
	total_len = calculate_total_length(head);
	result = (char *)malloc(total_len * sizeof(char));
	if (result == NULL)
		return (NULL);
	copy_to_buffer(head, result);
	return (result);
}

char	*expend_wild_card(char *arg)
{
	t_entry *entries;
	char *result;
	char *pattern;

	if (arg == NULL)
		return (NULL);
	pattern = arg;
	entries = get_all_entries();
	if (entries == NULL)
		return (NULL);
	entries = filter_entries_by_pattern(entries, pattern);
	if (entries == NULL)
		return (NULL);
	result = join_entries(entries);
	if (result == NULL)
	{
		free_entry_list(entries);
		return (NULL);
	}
	free_entry_list(entries);
	free(arg);
	return (result);
}
