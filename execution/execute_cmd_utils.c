/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:40:06 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/13 02:53:52 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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

static void	init_file_name(t_file *file, char *origin, t_shell *shell)
{
	char	*tmp;
	char	*buff;
	char	*ready;
	bool	in_quotes;

	free(file->name);
	free(file->limiter);
	free(file->raw);
	file->raw = ft_strdup(origin);
	buff = mark_quotes(origin);
	ready = expand_vars(buff, shell);
	tmp = ready;
	ready = remove_quotes(ready);
	free(tmp);
	file->name = ready;
	file->name = ready;
	file->has_quotes = !ft_strcmp(buff, ready);
	file->limiter = remove_quotes(buff);
}

// else if (redir->type == REDIR_HEREDOC)
// status = handle_redir_heredoc(cmd, redir);
int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	t_file	file;
	int		status;

	redir = cmd->redirs;
	file.name = NULL;
	file.limiter = NULL;
	file.raw = NULL;
	while (redir)
	{
		init_file_name(&file, redir->file_or_limiter, shell);
		if (redir->type == REDIR_IN)
			status = handle_redir_in(cmd, &file);
		else if (redir->type == REDIR_OUT)
			status = handle_redir_out(cmd, &file);
		else if (redir->type == REDIR_APPEND)
			status = handle_redir_append(cmd, &file);
		if (status != 0)
			return (status);
		redir = redir->next;
	}
	return (0);
}
