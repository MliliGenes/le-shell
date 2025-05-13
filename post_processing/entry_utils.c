/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:22:35 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:22:41 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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

void	print_entries(t_entry *head)
{
	t_entry	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

t_entry	*get_all_entries(void)
{
	DIR *dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);

	t_entry *head = NULL;
	struct dirent *entry;
	while ((entry = readdir(dir)))
	{
		t_entry *new = create_entry(entry->d_name);
		if (!new)
		{
			free_entry_list(head);
			return (NULL);
		}
		add_back_entry(&head, new);
	}
	closedir(dir);
	return (head);
}