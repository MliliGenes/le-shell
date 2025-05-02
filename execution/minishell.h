/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:20:58 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/02 20:19:09 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include "include/libft.h"
# include "include/readline.h"
# include "include/history.h"

extern int				exit_status;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_env_kv
{
	char				*key;
	char				*value;
	int					has_value;
}						t_env_kv;

// utils functions:
int						count_2d(char **arr);
void					free_2d(char **arr);
char					*expand_exit_status(char *input);
int						is_valid_key(char *str);
int						key_exist(t_env_var *env_list, char *key);

// builtins functions:
void					exec_builtins(char *input, t_env_var **env_list);
void					handle_pwd(char *input);
void					handle_echo(char *input);
void					handle_exit(char *input);
void					handle_env(char *input, t_env_var *env_list);
void					handle_export(char *input, t_env_var **env_list);
void					handle_unset(char *input, t_env_var **env_list);
void					handle_cd(char *input, t_env_var *env_list);

// env
t_env_var				*init_env(char *envp[]);
void					free_env_list(t_env_var *head);
t_env_var				*handle_empty_env();
t_env_var				*create_env_var(char *key, char *value);
void					add_env_back(t_env_var **head, t_env_var *new);
void					env_update(t_env_var *env_list, char *key, char *value);

void					handle_wildcards(char *input);

#endif
