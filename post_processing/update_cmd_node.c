/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:08:16 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 00:55:33 by sel-mlil         ###   ########.fr       */
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
	char 	*joined;

	if (!cmd || !cmd->args)
		return ;
	index = 0;
	while (cmd->args && cmd->args[index])
	{
		cmd->args[index] = expand_wildcard(cmd->args[index]);
		index++;
	}
	joined = holy_joint(cmd->args);
	cmd->args = holy_split(joined);
	if (cmd->args)
		cmd->cmd = cmd->args[0];
}

void	update_cmd_node(t_cmd *cmd, t_shell *shell)
{
	char	**new_args;
	char	*expended_arg;
	char	*tmp;
	char	*join_arg;
	int		index_old;

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
	index_old = 0;
	while (new_args && new_args[index_old])
	{
		tmp = new_args[index_old];
		new_args[index_old] = remove_quotes(new_args[index_old]);
		free(tmp);
		index_old++;
	}
	cmd->args = new_args;
	if (cmd->args)
		cmd->cmd = cmd->args[0];
	apply_wild_card(cmd);
}
