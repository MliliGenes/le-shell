/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expention.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:36:33 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/29 12:43:36 by sel-mlil         ###   ########.fr       */
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

void	process_variable_length(t_expansion *exp)
{
	int		start;
	char	*key;
	char	*value;

	exp->i_index++;
	start = exp->i_index;
	exp->len--;
	while (exp->input[exp->i_index] && (ft_isalnum(exp->input[exp->i_index])
			|| exp->input[exp->i_index] == '_'))
	{
		exp->len--;
		exp->i_index++;
	}
	key = ft_substr(exp->input, start, exp->i_index - start);
	value = find_env_var(exp->vars, key);
	if (value)
		exp->len += strlen(value);
	free(key);
}

void	calculate_expanded_length(t_expansion *exp)
{
	while (exp->input[exp->i_index])
	{
		update_quote_state(exp, exp->input[exp->i_index]);
		if (!exp->s_quote && exp->input[exp->i_index] == '$'
			&& (ft_isalnum(exp->input[exp->i_index + 1]) || exp->input[exp->i_index
				+ 1] == '_'))
			process_variable_length(exp);
		else
			exp->i_index++;
	}
	exp->i_index = 0;
}

char	*extract_var_name(t_expansion *exp)
{
	int	start;
	int	length;

	start = exp->i_index;
	length = 0;
	while (exp->input[exp->i_index] && (ft_isalnum(exp->input[exp->i_index])
			|| exp->input[exp->i_index] == '_'))
	{
		exp->i_index++;
		length++;
	}
	return (ft_substr(exp->input, start, length));
}

void	expand_variable(t_expansion *exp)
{
	char	*key;
	char	*value;
	int		value_index;

	value_index = 0;
	exp->i_index++;
	key = extract_var_name(exp);
	value = find_env_var(exp->vars, key);
	if (value)
	{
		while (value[value_index])
			exp->output[exp->o_index++] = value[value_index++];
	}
	free(key);
}

char	*expand_vars(char *input, t_env_var *vars)
{
	t_expansion	exp;

	init_expansion(&exp, input, vars);
	calculate_expanded_length(&exp);
	exp.output = (char *)malloc(exp.len + 1);
	if (!exp.output)
		return NULL;
	while (input[exp.i_index])
	{
		update_quote_state(&exp, input[exp.i_index]);
		if (!exp.s_quote && input[exp.i_index] == '$'
			&& (ft_isalpha(input[exp.i_index + 1]) || input[exp.i_index
				+ 1] == '_'))
			expand_variable(&exp);
		else
			exp.output[exp.o_index++] = input[exp.i_index++];
	}
	exp.output[exp.o_index] = 0;
	return exp.output;
}

void	update_cmd_node(t_ready_token *node)
{

}
