/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:42:39 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/28 01:54:07 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int match(char *filename, char *pattern)
{
	(void)filename;
	if (ft_strcmp(pattern, "*") == 0)
		return (1);
	if (pattern[0] == '*' && pattern[ft_strlen(pattern) - 1] != '*')
	{
		char *text = pattern + 1;
		int len = ft_strlen(text);
		int file_len = ft_strlen(filename);
		if (file_len >= len && ft_strcmp(filename + file_len - len, text) == 0)
			return (1);
	}
	else if (pattern[ft_strlen(pattern) - 1] == '*' && pattern[0] != '*')
    {
        int len = ft_strlen(pattern) - 1;
        if (ft_strncmp(filename, pattern, len) == 0)
            return (1);
    }
	return (0);
}

void	expand_full(char **arg)
{
	(void)arg;
	DIR *dir;
	struct dirent *entry;
	
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return;
	}
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name, "..") != 0 
			&& match(entry->d_name, *arg))
			printf("%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
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
			expand_full(&args[i]);
		i++;			
	}
	free_2d(args);
}