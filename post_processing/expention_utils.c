/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:36:33 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 04:01:35 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*find_env_var(t_shell *shell, const char *key)
{
	t_env_var	*env_vars;

	env_vars = shell->env;
	if (ft_strcmp("?", key) == 0)
		return (ft_itoa(shell->last_status));
	while (key && env_vars != NULL)
	{
		if (ft_strcmp(env_vars->key, key) == 0)
			return (ft_strdup(env_vars->value));
		env_vars = env_vars->next;
	}
	return (NULL);
}

void	init_expansion(t_expansion *exp, char *input, t_shell *shell)
{
	exp->input = input;
	exp->len = ft_strlen(input);
	exp->s_quote = 0;
	exp->d_quote = 0;
	exp->i_index = 0;
	exp->o_index = 0;
	exp->shell = shell;
}

void	update_quote_state(t_expansion *exp, char current_char)
{
	if (current_char == 1 && !exp->d_quote)
		exp->s_quote = !exp->s_quote;
	if (current_char == 2 && !exp->s_quote)
		exp->d_quote = !exp->d_quote;
}
