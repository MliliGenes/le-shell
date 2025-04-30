/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:36:33 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/29 15:57:49 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*find_env_var(t_env_var *env_vars, const char *key)
{
	while (env_vars != NULL)
	{
		if (ft_strcmp(env_vars->key, key) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

void	init_expansion(t_expansion *exp, char *input, t_env_var *vars)
{
	exp->input = input;
	exp->len = ft_strlen(input);
	exp->s_quote = 0;
	exp->d_quote = 0;
	exp->i_index = 0;
	exp->o_index = 0;
	exp->vars = vars;
}

void	update_quote_state(t_expansion *exp, char current_char)
{
	if (current_char == '\'' && !exp->d_quote)
		exp->s_quote = !exp->s_quote;
	if (current_char == '\"' && !exp->s_quote)
		exp->d_quote = !exp->d_quote;
}
