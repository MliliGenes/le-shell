/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_docs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 06:17:40 by le-saad           #+#    #+#             */
/*   Updated: 2025/05/15 04:53:32 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/signals.h"
#include <sys/_types/_pid_t.h>
#include <sys/wait.h>

int	pipe_fork_read(t_redir *redirs)
{
	int		fd[2];
	pid_t	pid;
    int		status;

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
	close(fd[1]);
	if (pid == 0)
	{
		reset_signals_for_child();
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		readline("> ");
		close(fd[1]);
		exit(0);
	}
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
    if (status != 0)
    {
        close(fd[0]);
        return (1);
    }
	redirs->here_doc_read = fd[0];
	return (0);
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
		{
			printf("Here doc: %s\n", redirs->file_or_limiter);
		}
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
		}
		curret = curret->next;
	}
	return (status);
}
