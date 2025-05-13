/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:35:10 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/13 04:58:05 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "builtins.h"

char	*get_cmd_path(t_cmd *cmd, char **paths);
char	**env_to_array(t_env_var *env);
int		execute_command(t_cmd *cmd, t_shell *shell);
int		apply_redirections(t_cmd *cmd, t_shell *shell);
int		handle_ambiguous(char *name, char *raw);

int		handle_redir_in(t_cmd *cmd, t_file *file);
int		handle_redir_out(t_cmd *cmd, t_file *file);
int		handle_redir_append(t_cmd *cmd, t_file *file);
int		handle_redir_heredoc(t_cmd *cmd, t_file *file);

int     handle_pipe(t_ast *node, t_shell *shell);
int     handle_and(t_ast *node, t_shell *shell);
int     handle_or(t_ast *node, t_shell *shell);

void	cleanup_fds(t_cmd *cmd);
void	save_std_fds(int *saved_stdin, int *saved_stdout);
void	restore_std_fds(int saved_stdin, int saved_stdout);
void	apply_fds(t_cmd *cmd);

int     execute_ast_node(t_ast *node, t_shell *shell);

char	*find_env_var(t_shell *shell, const char *key);
void	init_expansion(t_expansion *exp, char *input, t_shell *shell);
void	update_quote_state(t_expansion *exp, char current_char);
char	*holy_joint(char **args);
int		holy_count_words(char *str);
char	**holy_split(char *joint);
char	*expand_vars(char *input, t_shell *shell);
void	update_quote_status(char c, bool *in_single, bool *in_double);
void	update_quote_status_new(char c, bool *in_single, bool *in_double);
bool	is_in_quote(bool in_single, bool in_double);
char	*remove_quotes(char *str);
char	*mark_quotes(char *str);
void	update_cmd_node(t_cmd *cmd, t_shell *shell);

#endif