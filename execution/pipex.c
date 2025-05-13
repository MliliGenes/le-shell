/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:25:05 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/13 17:00:49 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int handle_pipe(t_ast* node, t_shell *shell)
{
    int pipefd[2];
    pid_t left_pid, right_pid;

    if (pipe(pipefd) == -1)
        return (perror("pipe"), 1);
    shell->fork_level++;
    left_pid = fork();
    if (left_pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (left_pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(execute_ast(node->left, shell));
    }
    
    right_pid = fork();
    if (right_pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (right_pid == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(execute_ast(node->right, shell));
    }    
    shell->fork_level--;
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, &shell->last_status, 0);
    return (WEXITSTATUS(shell->last_status));
}

int handle_and(t_ast *node, t_shell *shell)
{
    int left_status = execute_ast(node->left, shell);
    if (left_status == 0) {
        return execute_ast(node->right, shell);
    }    
    return left_status;
}

int handle_or(t_ast *node, t_shell *shell)
{
    int left_status = execute_ast(node->left, shell);
    if (left_status != 0) {
        return execute_ast(node->right, shell);
    }    
    return left_status;
}
