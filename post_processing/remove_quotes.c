/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:28:50 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 22:32:24 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

// TODO : RM THE FUCKING QUOTES
char	*remove_quotes(char *str)
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
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		update_quote_status(str[i], &s_quote, &d_quote);
		if ((str[i] == '\'' && !d_quote) || (str[i] == '"' && !s_quote))
		{
			i++;
			continue ;
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
