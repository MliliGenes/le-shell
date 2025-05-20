/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:05:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/19 16:19:11 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution_bonus.h"
#include "../include/parsing_bonus.h"

int	handle_ambiguous(bool quoted, char *name, char *raw)
{
	if (!quoted && (!*name || empty(name) || holy_count_words(name) > 1))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(raw, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	handle_redir_in(t_cmd *cmd, t_file *file)
{
	int	fd;

	if (handle_ambiguous(file->multiple_words, file->name, file->raw))
		return (1);
	fd = open(file->name, O_RDONLY);
	if (fd < 0)
	{
		perror(file->name);
		return (1);
	}
	if (cmd->fds[0] != STDIN_FILENO)
		close(cmd->fds[0]);
	cmd->fds[0] = fd;
	return (0);
}

int	handle_redir_out(t_cmd *cmd, t_file *file)
{
	int	fd;

	if (handle_ambiguous(file->multiple_words, file->name, file->raw))
		return (1);
	fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file->name);
		return (1);
	}
	if (cmd->fds[1] != STDOUT_FILENO)
		close(cmd->fds[1]);
	cmd->fds[1] = fd;
	return (0);
}

int	handle_redir_append(t_cmd *cmd, t_file *file)
{
	int	fd;

	if (handle_ambiguous(file->multiple_words, file->name, file->raw))
		return (1);
	fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file->name);
		return (1);
	}
	if (cmd->fds[1] != STDOUT_FILENO)
		close(cmd->fds[1]);
	cmd->fds[1] = fd;
	return (0);
}

int	handle_redir_heredoc(t_cmd *cmd, t_redir *redir, t_file *file,
		t_shell *shell)
{
	if (redir->here_doc_read != -1 && !file->herdoc)
	{
		if (update_heredoc_pipe(redir, shell))
			return (1);
	}
	if (redir->here_doc_read != -1)
	{
		cmd->fds[0] = redir->here_doc_read;
		redir->here_doc_read = -1;
	}
	return (0);
}
