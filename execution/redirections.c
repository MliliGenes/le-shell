/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:05:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/12 20:20:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

static int empty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!is_white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int handle_ambiguous(char *expanded, char *dequoted, char *raw)
{
	if (ft_strcmp(expanded, dequoted) == 0)
	{
		if (!dequoted || empty(dequoted) || holy_count_words(dequoted) > 1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(raw, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

int handle_redir_in(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int handle_redir_out(const char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int handle_redir_append(const char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
