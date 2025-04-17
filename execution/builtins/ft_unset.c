/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:52:54 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/17 22:48:31 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void env_remove(t_env_var **env_list, char *key)
{
	t_env_var *curr = *env_list;
	t_env_var *prev = NULL;
	t_env_var *tmp;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			tmp = curr->next;
			if (prev)
				prev->next = tmp;
			else
				*env_list = tmp;
			free(curr->key);
			free(curr->value);
			free(curr);
			curr = tmp;
			continue;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	handle_unset(char *input, t_env_var **env_list)
{
	char **args;
	int i;

	i = 1;
	args = ft_split(input, ' ');
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "unset") == 0)
	{
		while (args[i])
		{
			if (!is_valid_key(args[i]))
			{
				ft_putstr_fd("unset: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
			}
			else if (key_exist(*env_list, args[i]))
				env_remove(env_list, args[i]);
			i++;
		}
	}
	free_2d(args);
}
