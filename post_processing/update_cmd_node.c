/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:08:16 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 19:08:12 by sel-mlil         ###   ########.fr       */
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

static int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static int	empty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!is_white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	update_cmd_node(t_cmd *cmd, t_shell *shell)
{
	char	**new_args;
	char	*expended_arg;
	char	*tmp;
	char	*join_arg;
	int		index_old;

	join_arg = holy_joint(cmd->args);
	if (has_quotes(join_arg))
		join_arg = mark_quotes(join_arg);
	expended_arg = expand_vars(join_arg, shell);
	free(join_arg);
	new_args = holy_split(expended_arg);
	index_old = 0;
	while (new_args[index_old])
	{
		new_args[index_old] = remove_quotes(new_args[index_old]);
		index_old++;
	}
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
}
