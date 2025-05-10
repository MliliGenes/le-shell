/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:28:50 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/09 18:38:03 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

// TODO : RM THE FUCKING QUOTES
char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	char	quote_type;
	
	i = 0;
	j = 0;
	quote_type = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote_type)
				quote_type = str[i];
			else if (quote_type == str[i])
				quote_type = 0;
			i++;
			continue ;
		}
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
