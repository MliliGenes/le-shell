/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:08:16 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/11 23:46:00 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


static int empty(char *str)
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
	int		index_old;
	bool	quoted;
	int		index_new;

	index_old = 0;
	index_new = 0;
	new_args = malloc(sizeof(char *) * (args_count(cmd->args) + 1));
	if (!new_args)
		return ;
	while (cmd->args && cmd->args[index_old])
	{
		quoted = has_quotes(cmd->args[index_new]);
		expended_arg = expand_vars(cmd->args[index_old], shell);
		if (quoted)
		{
			tmp = expended_arg;
			expended_arg = remove_quotes(expended_arg);
			free(tmp);
		}
		if (!quoted && (!*expended_arg || empty(expended_arg)))
		{
			free(expended_arg);
			index_old++;
			continue ;
		}
		new_args[index_new] = expended_arg;
		index_new++;
		index_old++;
	}
	new_args[index_new] = NULL;
	free_2d(cmd->args);
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
}
