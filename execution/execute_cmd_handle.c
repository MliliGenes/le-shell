/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 20:22:55 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
} 

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*expended;
	char	*dequoted;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		expended = expand_vars(redir->file_or_limiter, shell);
		dequoted = remove_quotes(expended);
		if (handle_ambiguous(expended, dequoted, redir->file_or_limiter))
		{
			free(expended);
			free(dequoted);
			return (1);
		}
		free(expended);
		if (redir->type == REDIR_IN)
			fd = handle_redir_in(dequoted);
		else if (redir->type == REDIR_OUT)
			fd = handle_redir_out(dequoted);
		else if (redir->type == REDIR_APPEND)
			fd = handle_redir_append(dequoted);
		redir = redir->next;
	}
	return (0);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**tmp_env;

	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	update_cmd_node(cmd, shell);
	if (is_builtin(cmd->cmd))
		return (execute_builtins_with_redir(cmd, shell));
	cmd_path = get_cmd_path(cmd, shell->path);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	tmp_env = env_to_array(shell->env);
	if (pid == 0)
	{
		if (cmd->redirs)
			if (apply_redirections(cmd, shell) != 0)
				exit(1);
		execve(cmd_path, cmd->args, tmp_env);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	free_2d(tmp_env);
	return (WEXITSTATUS(status));
}
