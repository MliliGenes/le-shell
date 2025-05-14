/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:08:16 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 06:23:16 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/parsing.h"

static bool	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

void	apply_wild_card(t_cmd *cmd)
{
	int		index;
	char	*tmp;
	char	*joined;
	char	**new_args;

	if (!cmd || !cmd->args)
		return ;
	index = 0;
	while (cmd->args && cmd->args[index])
	{
		cmd->args[index] = mark_astrestisk(cmd->args[index]);
		tmp = cmd->args[index];
		cmd->args[index] = remove_quotes(cmd->args[index]);
		free(tmp);
		cmd->args[index] = expand_wildcard(cmd->args[index]);
		cmd->args[index] = reset_astrestisk(cmd->args[index]);
		index++;
	}
	// joined = holy_joint(cmd->args);
	// new_args = holy_split(joined);
	// cmd->args = new_args;
}

void	update_cmd_node(t_cmd *cmd, t_shell *shell)
{
	char	**new_args;
	char	*expended_arg;
	char	*join_arg;

	if (!cmd || !cmd->args)
		return ;
	join_arg = holy_joint(cmd->args);
	if (join_arg && has_quotes(join_arg))
		join_arg = mark_quotes(join_arg);
	expended_arg = expand_vars(join_arg, shell);
	free(join_arg);
	if (!expended_arg)
		return ;
	new_args = holy_split(expended_arg);
	free(expended_arg);
	cmd->args = new_args;
	apply_wild_card(cmd);
	if (cmd->args)
		cmd->cmd = cmd->args[0];
}
