/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utilc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:19:45 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/07 21:23:55 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		handle_cd(cmd->args, shell->env);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		handle_unset(cmd->args, &shell->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		handle_export(cmd->args, &shell->env);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		handle_env(shell->env);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		handle_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		handle_pwd();
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		handle_exit(cmd->args, shell);
	else
		return (1);
	return (0);
}
