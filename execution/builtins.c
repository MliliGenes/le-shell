/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:11:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/22 01:00:11 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_builtins(char *input, t_env_var **env_list)
{
    handle_pwd(input);
    handle_echo(input);
    handle_exit(input);
    handle_env(input, *env_list);
    handle_export(input, env_list);
    handle_unset(input, env_list);
    handle_cd(input, *env_list);
}