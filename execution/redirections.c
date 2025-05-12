/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:05:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/12 14:23:12 by le-saad          ###   ########.fr       */
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

int handle_redir_in(const char *filename, t_cmd *cmd)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(filename), 1);
	if (cmd->fds[0] != STDIN_FILENO)
		close(cmd->fds[0]);	
	cmd->fds[0] = fd;
	return (0);
}

int handle_redir_out(const char *filename, t_cmd *cmd)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	if (cmd->fds[1] != STDOUT_FILENO)
		close(cmd->fds[1]);
	cmd->fds[1] = fd;
	return (0);
}

int handle_redir_append(const char *filename, t_cmd *cmd)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	if (cmd->fds[1] != STDOUT_FILENO)
		close(cmd->fds[1]);
	cmd->fds[1] = fd;
	return (0);
}
