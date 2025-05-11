/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 20:10:40 by ssbaytri         ###   ########.fr       */
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
	char	*tmp;
	char	*tmp2;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		tmp = expand_vars(redir->file_or_limiter, shell);
		tmp2 = remove_quotes(tmp);
		if (ft_strcmp(tmp2, tmp) == 0)
		{
			if (!tmp2 || !tmp2[0] || ft_strchr(tmp2, ' ') || ft_strchr(tmp2,
					'\t') || ft_strchr(tmp2, '\n'))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_or_limiter, STDERR_FILENO);
				ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
				free(tmp);
				free(tmp2);
				return (1);
			}
		}
		free(tmp);
		if (redir->type == REDIR_IN)
		{
			fd = open(tmp2, O_RDONLY);
			if (fd < 0)
			{
				perror(tmp2);
				free(tmp2);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(tmp2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(tmp2);
				free(tmp2);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(tmp2, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(tmp2);
				free(tmp2);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		free(tmp2);
		redir = redir->next;
	}
	return (0);
}

void	print_args(char **args)
{
	int	i;

	printf("Updating args...\n");
	i = 0;
	while (args && args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	printf("Updated args\n");
}

void	update_args(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args && args[i])
	{
		tmp = remove_quotes(args[i]);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}

int	reset_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*joint_cmd;
	char	*expanded_args;

	joint_cmd = holy_joint(cmd->args);
	if (!joint_cmd)
		return (1);
	expanded_args = expand_vars(joint_cmd, shell);
	if (!expanded_args)
		return (free(expanded_args), 1);
	cmd->args = holy_split(expanded_args);
	free(expanded_args);
	if (!cmd->args)
		return (1);
	update_args(cmd->args);
	cmd->cmd = cmd->args[0];
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
	if (reset_cmd(cmd, shell))
		return (1);
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
