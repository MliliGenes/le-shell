/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:52:54 by ssbaytri          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/06 18:22:43 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
=======
/*   Updated: 2025/05/02 23:07:51 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
>>>>>>> 592d8acb6f76f104019ec385ef186264a06f64cc

static void	free_env_node(t_env_var *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static void	env_remove(t_env_var **env_list, char *key)
{
	t_env_var	*curr;
	t_env_var	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

<<<<<<< HEAD
void	handle_unset(char **args, t_env_var **env_list)
{
	int	i;

	if (!args || !args[0])
		return ;
	i = 1;
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
=======
void	handle_unset(char *input, t_env_var **env_list)
{
	char	**args;
	int		i;

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
>>>>>>> 592d8acb6f76f104019ec385ef186264a06f64cc
}
