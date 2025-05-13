/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:25:28 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:35:56 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	*expand_wildcard(char *arg)
{
	t_entry	*entries;
	char	*result;

	if (!arg)
		return (NULL);
	entries = get_all_entries();
	if (!entries)
		return (arg);
	entries = filter_entries_by_pattern(entries, arg);
	if (!entries)
		return (arg);
	result = join_entries(entries);
	free_entry_list(entries);
	free(arg);
	return (result);
}
