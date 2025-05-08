/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/08 20:00:15 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"
#include "../include/execution.h"

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	while (*paths)
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

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**tmp_env;

	// if (cmd->redirs)
	// 	if (apply_redirections(cmd) != 0)
	// 		return (1);
	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	if (is_builtin(cmd->cmd))
		return (execute_builtin(cmd, shell));
	cmd_path = get_cmd_path(cmd, shell->path);
	if (!cmd_path)
		return (127);
	tmp_env = env_to_array((t_env_var *)shell->env);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd->args, tmp_env);
		exit(127);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	free(tmp_env);
	return (WEXITSTATUS(status));
}
