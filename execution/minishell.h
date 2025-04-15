/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:20:58 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/15 18:06:42 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "include/libft.h"
#include "include/readline.h"
#include "include/history.h"

extern int exit_status;

typedef struct s_env_var
{
	char						*key;
	char						*value;
	struct s_env_var			*next;
}								t_env_var;

// utils functions:
int count_2d(char **arr);
void free_2d(char **arr);
char *expand_exit_status(char *input);

// builtins functions:
void exec_builtins(char *input, t_env_var *env_list);
void handle_pwd(char *input);
void handle_echo(char *input);
void handle_exit(char *input);
void handle_env(char *input, t_env_var *env_list);

// env
t_env_var	*init_env(char *envp[]);
void free_env_list(t_env_var *head);
