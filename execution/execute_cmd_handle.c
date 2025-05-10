/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/09 18:28:08 by ssbaytri         ###   ########.fr       */
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

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->file_or_limiter, O_RDONLY);
			if (fd < 0)
				return (perror(redir->file_or_limiter), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->file_or_limiter, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd < 0)
				return (perror(redir->file_or_limiter), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file_or_limiter, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (fd < 0)
				return (perror(redir->file_or_limiter), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

void	update_args(char ***args)
{
	int	i;
	char **tmp;

	tmp = *args;
	i = 0;
	while (tmp[i])
	{
		tmp[i] = remove_quotes(tmp[i]);
		i++;
	}
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*joint_cmd;
	char	**new_args;	
	char	*cmd_path;
	char	**tmp_env;

	if (!cmd->cmd || !cmd->cmd[0])
		return (0);
	joint_cmd = holy_joint(cmd->args);
	joint_cmd = expand_vars(joint_cmd, shell);
	new_args = holy_split(joint_cmd);
	update_args(&new_args);
	cmd->args = new_args;
	if (cmd->args)
		cmd->cmd = cmd->args[0];
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
			if (apply_redirections(cmd) != 0)
				exit(1);
		execve(cmd_path, cmd->args, tmp_env);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	free(tmp_env);
	return (WEXITSTATUS(status));
}
