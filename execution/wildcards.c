/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:42:39 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/13 21:08:43 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	char	*newptr;

	if (ptr == NULL)
		return (malloc(newsize));
	if (newsize <= oldsize)
		return (ptr);
	newptr = malloc(newsize); 	
	if (!newptr)
		return (NULL);
	ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}


int ft_counter(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int match_split(char *filename, char **pieces)
{
	int i = 0;
	char *found;

	while (pieces[i])
	{
		found = ft_strnstr(filename, pieces[i], ft_strlen(filename));
		if (!found)
			return (0);
		filename = found + ft_strlen(pieces[i]);
		i++;
	}
	return (1);
}

static int match(char *filename, char *pattern)
{
	if (ft_strcmp(pattern, "*") == 0)
		return (1);
	if (pattern[0] == '*' && pattern[ft_strlen(pattern) - 1] != '*' && ft_counter(pattern, '*') == 1)
	{
		char *text = pattern + 1;
		int len = ft_strlen(text);
		int file_len = ft_strlen(filename);
		if (file_len >= len && ft_strcmp(filename + file_len - len, text) == 0)
			return (1);
	}
	else if (pattern[ft_strlen(pattern) - 1] == '*' && pattern[0] != '*' && ft_counter(pattern, '*') == 1)
    {
        int len = ft_strlen(pattern) - 1;
        if (ft_strncmp(filename, pattern, len) == 0)
            return (1);
    }
	else if (pattern[0] == '*' && pattern[ft_strlen(pattern) - 1] == '*' && ft_counter(pattern, '*') == 2)
	{
		char *text = ft_substr(pattern, 1, ft_strlen(pattern) - 2);
		if (!text)
			return (0);
		if (ft_strnstr(filename, text, ft_strlen(filename)))
		{
			free(text);
			return (1);
		}
		free(text);
	}
	else
	{
		char **split = ft_split(pattern, '*');
		if (!split)
			return (0);
		if (match_split(filename, split))
		{
			free_2d(split);
			return (1);
		}
		free_2d(split);
	}
	return (0);
}

char **get_matched(char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	char **matches;
	int count;

	matches = NULL;
	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return NULL;
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue;
		}
		if (match(entry->d_name, pattern))
		{
			matches = ft_realloc(matches, sizeof(char *) * count, sizeof(char *) * (count + 2));
			if (!matches)
				return (NULL);
			matches[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(dir);
	}
	if (matches)
		matches[count] = NULL;
	closedir(dir);
	return (matches);
}

void	sort_matches(char **matches)
{
	int		i, j;
	char	*tmp;

	if (!matches)
		return;
	for (i = 1; matches[i]; i++)
	{
		j = i;
		while (j > 0 && ft_strcmp(matches[j - 1], matches[j]) > 0)
		{
			tmp = matches[j];
			matches[j] = matches[j - 1];
			matches[j - 1] = tmp;
			j--;
		}
	}
}

void	expand_arg(char **arg)
{
	char **matches;
	char *joined;
	int i;
	char *tmp;
	char *tmp2;

	matches = get_matched(*arg);
	if (!matches || !matches[0])
	{
		free_2d(matches);
		return;
	}
	sort_matches(matches);
	joined = NULL;
	i = 0;
	while (matches[i])
	{
		tmp = joined;
		if (!joined)
			joined = ft_strdup(matches[i]);
		else
		{
			joined = ft_strjoin(joined, " ");
			tmp2 = joined;
			joined = ft_strjoin(joined, matches[i]);
			free(tmp2);
			free(tmp);
		}
		i++;
	}
	free_2d(matches);
	free(*arg);
	*arg = joined;
}

void handle_wildcards(char *input)
{
	char **args;
	int i;

	i = 1;
	args = ft_split(input, ' ');
	if (!args)
		return;
	while (args[i])
	{
		if (ft_strchr(args[i], '*') != NULL)
		{
			expand_arg(&args[i]);
			printf("%s\n", args[i]);
		}
		i++;
	}
	free_2d(args);
}