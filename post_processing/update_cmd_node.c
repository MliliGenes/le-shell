/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:08:16 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/14 01:59:21 by sel-mlil         ###   ########.fr       */
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

void	_update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == 1 && !(*in_double))
		*in_single = !(*in_single);
	else if (c == 2 && !(*in_single))
		*in_double = !(*in_double);
}

char	*mark_astrestisk(char *str)
{
	bool	s_quote;
	bool	d_quote;
	int		i;

	if (!str)
		return (NULL);
	s_quote = false;
	d_quote = false;
	i = 0;
	while (str[i])
	{
		_update_quote_status(str[i], &s_quote, &d_quote);
		if (str[i] == '*' && (d_quote || s_quote))
				str[i] = 3;
		i++;
	}	return (str);
}

char	*reset_astrestisk(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == 3)
			str[i] = '*';
		i++;
	}
	return (str);
}

void	apply_wild_card(t_cmd *cmd)
{
	int		index;
	char	*tmp;
	char	*joined;

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
	joined = holy_joint(cmd->args);
	cmd->args = holy_split(joined);
	cmd->cmd = cmd->args[0];
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
	if (cmd->args)
		cmd->cmd = cmd->args[0];
	apply_wild_card(cmd);
}
