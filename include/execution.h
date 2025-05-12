/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:35:10 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/12 20:21:03 by ssbaytri         ###   ########.fr       */
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
int 	handle_redir_in(const char *filename);
int		handle_redir_out(const char *filename);
int		handle_redir_append(const char *filename);

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