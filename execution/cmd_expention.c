/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expention.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:36:33 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/27 17:09:14 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*find_env_var(t_env_var *env_vars, const char *key)
{
	while (env_vars != NULL)
	{
		if (strcmp(env_vars->key, key) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

void	update_cmd_node(t_ready_token *node)
{
	// step 1: search and replace
	// word "hello $var $var2 "
	// word len = 10 - 1 = 9
	// len of var key is 3
	// word = 9 - 3 = 6
	// supposing the value is "world"
	// new_word = 6 + 5 = 11 \0
	// start copying from original word till $ and skip it
	// new_word = "hello " then copy from the value
	// new_word = "hello world"
	// step 2: split vars
	// step 3: trim quotes
}
