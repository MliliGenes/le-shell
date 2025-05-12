/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:28:50 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 01:58:16 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*remove_quotes(char *input)
{
	char	*res;
	int		i;
	int		j;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	j = 0;
	s_quote = false;
	d_quote = false;
	res = malloc(ft_strlen(input) + 1);
	if (!res)
		return (NULL);
	while (input[i])
	{
		update_quote_status( input[i], &s_quote, &d_quote);
		if ((input[i] == '\'' && !d_quote) || (input[i] == '"' && !s_quote))
		{
			i++;
			continue ;
		}
		res[j++] = input[i++];
	}
	res[j] = '\0';
	return (free(input), res);
}
