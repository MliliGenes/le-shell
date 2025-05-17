/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_docs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 06:17:40 by le-saad           #+#    #+#             */
/*   Updated: 2025/05/15 22:38:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"
#include <unistd.h>

char	*trunc_newline(char *line)
{
	char	*str;

	str = ft_strdup(line);
	if (!str)
		return (NULL);
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int	pipe_fork_write(t_redir *redirs)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*line;
	char	*line_tmp;
	char	*limiter;

	limiter = remove_quotes(mark_quotes(redirs->file_or_limiter));
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
	{
		reset_signals_for_heredoc();
		close(fd[0]);
		while (true)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, limiter) == 0)
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		if (line)
			free(line);
		close(fd[1]);
		exit(0);
	}
	free(limiter);
	close(fd[1]);
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	// if (WIFSIGNALED(status))
	// 	if (WTERMSIG(status) == SIGINT)
	// 		status = 130;
	if (status != 0)
	{
		close(fd[0]);
		return (status);
	}
	redirs->here_doc_read = fd[0];
	return (status);
}

int	here_docs_loop(t_cmd *cmd)
{
	t_redir	*redirs;
	int		status;

	redirs = cmd->redirs;
	status = 0;
	while (redirs)
	{
		if (redirs->type == REDIR_HEREDOC)
			status = pipe_fork_write(redirs);
		if (status != 0)
			return (status);
		redirs = redirs->next;
	}
	return (status);
}

int	open_here_docs(t_ready_token *tokens)
{
	t_ready_token	*curret;
	t_cmd			*cmd;
	int				status;

	curret = tokens;
	status = 0;
	while (curret)
	{
		if (curret->type == CMD)
		{
			cmd = (t_cmd *)curret->p_token;
			status = here_docs_loop(cmd);
		}
		if (status != 0)
			return (status);
		curret = curret->next;
	}
	return (status);
}
