/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:56:53 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/12 19:59:00 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int handle_pipe(t_ast *root, t_shell *shell)
{
	int pipefd[2];
	pid_t left_pid, right_pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);

	left_pid = fork();
	if (left_pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(execute)
	}
}