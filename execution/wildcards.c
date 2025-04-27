/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:35:21 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/28 00:31:18 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_wildcards(char **arg)
{
	(void)arg;
	DIR			*dir;
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
		if (ft_strchr(args[i], '*'))
			expand_wildcards(&args[i]);
		i++;			
	}
	free_2d(args);
}