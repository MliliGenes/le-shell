/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:23:06 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:23:14 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int wildcardMatch(const char *input, const char *pattern)
{
    if (*pattern == '\0')
        return (*input == '\0');
    if (*pattern == '*') {
        while (*(pattern + 1) == '*')
            pattern++;
        if (*(pattern + 1) == '\0')
            return 1;
        while (*input != '\0') {
            if (wildcardMatch(input, pattern + 1))
                return 1;
            input++;
        }
        return wildcardMatch(input, pattern + 1);
    }
    if (*input != '\0' && (*pattern == *input))
        return wildcardMatch(input + 1, pattern + 1);
    return 0;
}

t_entry *filter_entries_by_pattern(t_entry *old, const char *pattern)
{
    t_entry *new_list = NULL;
    t_entry *current = old;
    
    while (current) {
        if (pattern[0] == '*' && *current->value == '.') {
            current = current->next;
        }
        else if (wildcardMatch(current->value, pattern)) {
            t_entry *new_entry = create_entry(current->value);
            if (!new_entry)
                return NULL;
            add_back_entry(&new_list, new_entry);
        }
        current = current->next;
    }
    free_entry_list(old);
    return new_list;
}