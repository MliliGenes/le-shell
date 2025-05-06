/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:09:18 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/06 15:50:41 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "structs.h"
#include "lib.h"

int						is_valid_key(char *str);
int						key_exist(t_env_var *env_list, char *key);
void					free_2d(char **arr);

void	handle_pwd(void);
void	handle_echo(char **args);
void	handle_exit(char **args, t_shell *shell);
void	handle_env(t_env_var *env);
void	handle_export(char **args, t_env_var **env_list);
void	handle_unset(char **args, t_env_var **env_list);
void    handle_cd(char **args, t_env_var *env);

// env
t_env_var				*init_env(char *envp[]);
void					free_env_list(t_env_var *head);
t_env_var				*handle_empty_env();
t_env_var				*create_env_var(char *key, char *value);
void					add_env_back(t_env_var **head, t_env_var *new);
void					env_update(t_env_var *env_list, char *key, char *value);