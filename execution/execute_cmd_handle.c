/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/08 17:20:12 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "exit"));
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		handle_cd(cmd->args, shell->env);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		handle_unset(cmd->args, &shell->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		handle_export(cmd->args, &shell->env);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		handle_env(shell->env);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		handle_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		handle_pwd();
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		handle_exit(cmd->args, shell);
	else
		return (1);
	return (0);
}

// TODO env_to_array(shell->env)
// TODO get_cmd_path(char *cmd)
// TODO apply_redirs(t_cmd *cmd)

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**tmp_env;

	// if (cmd->redirs)
	// 	if (apply_redirections(cmd->redirs) != 0)
	// 		return (1);
	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	if (is_builtin(cmd->cmd))
		return (execute_builtin(cmd, shell));
	// cmd_path = get_cmd_path(cmd->cmd, shell->path);
	// if (!cmd_path)
	// 	return (127);
	// tmp_env = env_to_array(shell->env);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd->args, tmp_env);
		exit(127);
	}
	waitpid(pid, &status, 0);
	// free(cmd_path);
	// free(tmp_env);
	return (WEXITSTATUS(status));
}
