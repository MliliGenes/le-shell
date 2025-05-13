/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/13 02:41:24 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

void	cleanup_fds(t_cmd *cmd)
{
	if (cmd->fds[0] != STDIN_FILENO)
		close(cmd->fds[0]);
	if (cmd->fds[1] != STDOUT_FILENO)
		close(cmd->fds[1]);
}

void	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	apply_fds(t_cmd *cmd)
{
	if (cmd->fds[0] != STDIN_FILENO)
	{
		dup2(cmd->fds[0], STDIN_FILENO);
		close(cmd->fds[0]);
	}
	if (cmd->fds[1] != STDOUT_FILENO)
	{
		dup2(cmd->fds[1], STDOUT_FILENO);
		close(cmd->fds[1]);
	}
}

int	handle_builtin(t_cmd *cmd, t_shell *shell)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	save_std_fds(&saved_stdin, &saved_stdout);
	if (cmd->fds[0] != STDIN_FILENO)
		dup2(cmd->fds[0], STDIN_FILENO);
	if (cmd->fds[1] != STDOUT_FILENO)
		dup2(cmd->fds[1], STDOUT_FILENO);
	status = execute_builtin(cmd, shell);
	restore_std_fds(saved_stdin, saved_stdout);
	cleanup_fds(cmd);
	return (status);
}

static int	handle_child_process(t_cmd *cmd, char *cmd_path, char **tmp_env)
{
	apply_fds(cmd);
	execve(cmd_path, cmd->args, tmp_env);
	perror("execve");
	free(cmd_path);
	free_2d(tmp_env);
	exit(127);
}

static int	handle_parent_process(pid_t pid, t_cmd *cmd, char *cmd_path,
		char **tmp_env)
{
	int	status;

	cleanup_fds(cmd);
	waitpid(pid, &status, 0);
	free(cmd_path);
	free_2d(tmp_env);
	return (WEXITSTATUS(status));
}

static int	handle_fork_error(char *cmd_path, char **tmp_env, t_cmd *cmd)
{
	perror("fork");
	free(cmd_path);
	free_2d(tmp_env);
	cleanup_fds(cmd);
	return (1);
}

static int	handle_cmd_not_found(t_cmd *cmd)
{
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	cleanup_fds(cmd);
	return (127);
}

int	handle_exec(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*cmd_path;
	char	**tmp_env;

	cmd_path = get_cmd_path(cmd, shell->path);
	if (!cmd_path)
		return (handle_cmd_not_found(cmd));
	tmp_env = env_to_array(shell->env);
	pid = fork();
	if (pid < 0)
		return (handle_fork_error(cmd_path, tmp_env, cmd));
	if (pid == 0)
		handle_child_process(cmd, cmd_path, tmp_env);
	return (handle_parent_process(pid, cmd, cmd_path, tmp_env));
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return (1);
	update_cmd_node(cmd, shell);
	apply_redirections(cmd, shell);
	if (!cmd->cmd || !cmd->cmd[0])
	{
		cleanup_fds(cmd);
		return (1);
	}
	if (is_builtin(cmd->cmd))
		return (handle_builtin(cmd, shell));
	return (handle_exec(cmd, shell));
}
