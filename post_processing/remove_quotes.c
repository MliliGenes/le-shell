/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:28:50 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 19:07:56 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	*mark_quotes(char *str)
{
	bool	s_quote;
	bool	d_quote;
	int		i;

	if (!str)
		return (NULL);
	s_quote = false;
	d_quote = false;
	i = 0;
	while (str[i])
	{
		update_quote_status(str[i], &s_quote, &d_quote);
		if ((str[i] == '\'' && !d_quote) || (str[i] == '"' && !s_quote))
		{
			if (str[i] == '\'')
				str[i] = 1;
			else
				str[i] = 2;
		}
		i++;
	}
	return (str);
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 1 || str[i] == 2)
		{
			i++;
			continue ;
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
