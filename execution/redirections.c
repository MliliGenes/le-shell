/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:05:57 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/15 07:35:00 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"
#include <stdio.h>

static int	empty(char *str)
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

int	handle_ambiguous(char *name, char *raw)
{
	if (!name || empty(name) || holy_count_words(name) > 1)
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

	if (!file->has_quotes && handle_ambiguous(file->name, file->raw))
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

	if (file->has_quotes == false && handle_ambiguous(file->name, file->raw))
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

	if (file->has_quotes == false && handle_ambiguous(file->name, file->raw))
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

int	update_heredoc_pipe(t_redir *redir, t_file *file, t_shell *shell)
{
	char	*line;
	char	*tmp;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	while (true)
	{
		line = get_line(redir->here_doc_read);
		if (!line)
			break ;
		tmp = line;
		line = expand_vars(tmp, shell);
		free(tmp);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	close(redir->here_doc_read);
	redir->here_doc_read = fd[0];
	return (0);
}

int	handle_redir_heredoc(t_cmd *cmd, t_redir *redir, t_file *file,
		t_shell *shell)
{
	if (redir->here_doc_read != -1 && !file->has_quotes)
	{
		if (update_heredoc_pipe(redir, file, shell))
			return (1);
	}
	if (redir->here_doc_read != -1)
	{
		cmd->fds[0] = redir->here_doc_read;
		redir->here_doc_read = -1;
	}
	return (0);
}
