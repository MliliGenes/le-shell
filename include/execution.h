/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:35:10 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/12 19:56:38 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "builtins.h"

char	*get_cmd_path(t_cmd *cmd, char **paths);
char	**env_to_array(t_env_var *env);
int		execute_command(t_cmd *cmd, t_shell *shell);
int		apply_redirections(t_cmd *cmd, t_shell *shell);
int		handle_ambiguous(char *expanded, char *dequoted, char *raw);
int		handle_redir_in(const char *filename);
int		handle_redir_out(const char *filename);
int		handle_redir_append(const char *filename);

int		handle_pipe(root, shell);

#endif