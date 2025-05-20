/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:40:06 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/20 20:14:53 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <stdbool.h>

int	check_path(t_cmd *path)
{
	struct stat	st;

	if (stat(path->cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) && ft_strchr(path->cmd, '/'))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path->cmd, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			cleanup_fds(path);
			return (126);
		}
		else if (ft_strchr(path->cmd, '/'))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path->cmd, STDERR_FILENO);
			ft_putstr_fd(": permission denied\n", STDERR_FILENO);
			cleanup_fds(path);
			return (126);
		}
	}
	ft_putstr_fd(path->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	cleanup_fds(path);
	return (127);
}

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	char		*tmp;
	char		*full_path;
	struct stat	sb;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (NULL);
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
	{
		if (access(cmd->cmd, F_OK) == 0 && stat(cmd->cmd, &sb) == 0
			&& S_ISREG(sb.st_mode) && access(cmd->cmd, X_OK) == 0)
			return (ft_strdup(cmd->cmd));
		return (NULL);
	}
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

static void	free_file(t_file *file)
{
	free(file->name);
	free(file->limiter);
	free(file->raw);
}

static void	init_file_name(t_file *file, char *origin, t_shell *shell)
{
	char	*tmp;
	char	*buff;
	char	*ready;
	int		i[2];

	free_file(file);
	file->raw = ft_strdup(origin);
	
	file->herdoc = false;
	file->bad_trip = false;
	
	buff = mark_quotes(file->raw);
	ready = expand_vars(buff, shell);
	
	if (has_quotes(buff))
		file->herdoc = true;

	tmp = ready;
	ready = remove_quotes(ready);
	
	printf("DEBUG  raw: %s ==> WORDS: %d\n", origin, holy_count_words(origin));
	
	i[0] = holy_count_words(tmp);
	i[1] = holy_count_words(ready);
	
	printf("DEBUG  expanded with qotes: %s ==> WORDS: %d\n", tmp, i[0]);
	printf("DEBUG  expanded without   : %s ==> WORDS: %d\n", ready, i[1]);
	
	
	if (i[0] == i[1] && ft_strcmp(origin, ready) != 0)
		file->bad_trip = true;
	
	file->bad_trip ? printf("should error out\n") : printf("should work\n");
	
	free(tmp);

	file->name = ready;
	file->limiter = remove_quotes(buff);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	t_file	file;
	int		status;

	redir = cmd->redirs;
	file.name = NULL;
	file.limiter = NULL;
	file.raw = NULL;
	status = 0;
	while (redir)
	{
		init_file_name(&file, redir->file_or_limiter, shell);
		if (redir->type == REDIR_IN)
			status = handle_redir_in(cmd, &file);
		else if (redir->type == REDIR_OUT)
			status = handle_redir_out(cmd, &file);
		else if (redir->type == REDIR_APPEND)
			status = handle_redir_append(cmd, &file);
		else if (redir->type == REDIR_HEREDOC)
			status = handle_redir_heredoc(cmd, redir, &file, shell);
		if (status != 0)
			return (free_file(&file), status);
		redir = redir->next;
	}
	return (free_file(&file), 0);
}
