/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:17:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/16 17:30:28 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int new_len(char *input, char *status_str)
{
	int i = 0;
	int len = 0;
	
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			len += ft_strlen(status_str);
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char *expand_exit_status(char *input)
{
	if (!input)
		return (NULL);
	char *status_str = ft_itoa(exit_status);
	int len = new_len(input, status_str);
	char *res = malloc(len + 1);
	if (!res)
	{
		free(status_str);
		return (NULL);
	}
	int i = 0, j = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			int k = 0;
			while (status_str[k])
				res[j++] = status_str[k++];
			i += 2;
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	free(status_str);
	return (res);
}
