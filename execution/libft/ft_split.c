/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:08:00 by ssbaytri          #+#    #+#             */
/*   Updated: 2024/11/05 04:06:45 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_split(char **arr, size_t j)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (i <= j)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < count_word(s, c) && i < ft_strlen(s))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[j++] = ft_substr(s, start, i - start);
		if (!arr[j - 1])
			return (free_split(arr, j - 1));
	}
	arr[j] = NULL;
	return (arr);
}
