/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:17:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/02 20:11:49 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	new_len(char *input, char *status_str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
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

char	*expand_exit_status(char *input)
{
	char	*status_str;
	int		len;
	char	*res;
	int		i = 0, j;
	int		k;

	if (!input)
		return (NULL);
	status_str = ft_itoa(exit_status);
	len = new_len(input, status_str);
	res = malloc(len + 1);
	if (!res)
	{
		free(status_str);
		return (NULL);
	}
	i = 0, j = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			k = 0;
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
