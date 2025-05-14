/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:25:28 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 05:12:24 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int sort_entries_bubble(t_entry *head)
{
    // Return early if list is empty or has only one element
    if (!head || !head->next)
        return 0;
    
    // Count the number of nodes
    int count = 0;
    t_entry *current = head;
    while (current)
    {
        count++;
        current = current->next;
    }
    
    // Allocate array to hold all values
    char **values = (char **)malloc(sizeof(char *) * count);
    if (!values)
        return -1; // Memory allocation failed
    
    // Copy all values to the array
    current = head;
    for (int i = 0; i < count; i++)
    {
        values[i] = current->value;
        current = current->next;
    }
    
    // Bubble sort the array using strcmp
    int swapped;
    char *temp;
    for (int i = 0; i < count - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < count - i - 1; j++)
        {
            if (ft_strcmp(values[j], values[j + 1]) > 0)
            {
                // Swap values[j] and values[j + 1]
                temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // If no swapping occurred in this pass, array is sorted
        if (swapped == 0)
            break;
    }
    
    // Reconstruct the linked list with sorted values
    current = head;
    for (int i = 0; i < count; i++)
    {
        current->value = values[i];
        current = current->next;
    }
    
    // Free the temporary array
    free(values);
    
    return 0;
}

char	*expand_wildcard(char *arg)
{
	t_entry	*entries;
	char	*result;

	if (!arg)
		return (NULL);
	entries = get_all_entries();
	if (!entries )
		return (arg);
	entries = filter_entries_by_pattern(entries, arg);
	if (!entries)
		return (arg);
	result = join_entries(entries);
	free_entry_list(entries);
	free(arg);
	return (result);
}
