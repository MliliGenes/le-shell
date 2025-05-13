/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:54:34 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/13 16:55:33 by ssbaytri         ###   ########.fr       */
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
	int		res;

	redir = cmd->redirs;
	while (redir)
	{
		res = 0;
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
			res = handle_redir_in(dequoted);
		else if (redir->type == REDIR_OUT)
			res = handle_redir_out(dequoted);
		else if (redir->type == REDIR_APPEND)
			res = handle_redir_append(dequoted);
		if (res != 0)
			return (free(dequoted), 1);
		redir = redir->next;
	}
	return (0);
}

int execute_command(t_cmd *cmd, t_shell *shell)
{
    char *cmd_path;
    char **tmp_env;
    int status;

    if (!cmd->cmd || !cmd->cmd[0])
        return (0);

    update_cmd_node(cmd, shell);

    // 🔸 Case 1: It's a built-in
    if (is_builtin(cmd->cmd))
    {
        // 🔹 No pipeline: run directly (e.g., `cd`, `export`)
        if (shell->fork_level == 0)
            return (execute_builtins_with_redir(cmd, shell));

        // 🔹 In pipeline: fork for I/O isolation
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return (1);
        }

        if (pid == 0) // Child
        {
            if (cmd->redirs && apply_redirections(cmd, shell) != 0)
                exit(1);
            exit(execute_builtins_with_redir(cmd, shell));
        }

        // Parent
        waitpid(pid, &status, 0);
        return (WEXITSTATUS(status));
    }

    // 🔸 Case 2: External command
    cmd_path = get_cmd_path(cmd, shell->path);
    if (!cmd_path)
    {
        ft_putstr_fd(cmd->cmd, STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        return (127);
    }

    // 🔹 shell->fork_level == 0: top-level command, we fork
    if (shell->fork_level == 0)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            free(cmd_path);
            return (1);
        }

        if (pid == 0)
        {
            tmp_env = env_to_array(shell->env);
            if (cmd->redirs && apply_redirections(cmd, shell) != 0)
                exit(1);
            execve(cmd_path, cmd->args, tmp_env);
            perror("execve");
            free_2d(tmp_env);
            exit(127);
        }

        waitpid(pid, &status, 0);
        free(cmd_path);
        return (WEXITSTATUS(status));
    }
    else
    {
        // 🔹 Already in a fork (pipe child): exec directly
        tmp_env = env_to_array(shell->env);
        if (cmd->redirs && apply_redirections(cmd, shell) != 0)
        {
            free_2d(tmp_env);
            return (1);
        }
        execve(cmd_path, cmd->args, tmp_env);
        perror("execve");
        free_2d(tmp_env);
        exit(127);
    }
}

