/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 02:40:06 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 10:24:18 by le-saad          ###   ########.fr       */
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

static free_file(t_file *file)
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

	free_file(file);
	file->raw = ft_strdup(origin);
	buff = mark_quotes(file->raw);
	buff = mark_astrestisk(buff);
	tmp = ready;
	ready = expand_vars(buff, shell);
	free(tmp);
	ready = expand_wildcard(ready);
	ready = reset_astrestisk(ready);
	tmp = ready;
	ready = remove_quotes(ready);
	free(tmp);
	file->name = ready;
	if (ft_strcmp(buff, ready) == 0)
	    file->has_quotes = false;
	else
	    file->has_quotes = true;
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
			return (free_file(&file), status);
		redir = redir->next;
	}
    free_file(&file);
	return (0);
}
