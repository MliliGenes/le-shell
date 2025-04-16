/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:42:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/16 17:32:05 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_var **create_env_ptr_arr(t_env_var *env)
{
	int size;
	t_env_var *tmp;
	t_env_var **arr;
	
	tmp = env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(t_env_var *) * (size + 1));
	if (!arr)
		return (NULL);
	int i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return arr;
}

void	sort_env_ptr_arr(t_env_var **arr)
{
	for (int i = 0; arr[i]; i++)
	{
		for (int j = i + 1; arr[j]; j++)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				t_env_var *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void	print_export(t_env_var *env_list)
{
	t_env_var **arr = create_env_ptr_arr(env_list);
	sort_env_ptr_arr(arr);
	for (int i = 0; arr[i]; i++)
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
	}
	free(arr);
}

void	handle_export(char *input, t_env_var *env_list)
{
	char **args = ft_split(input, ' ');
	if (!args)
		return ;
	if (ft_strcmp(args[0], "export") == 0 && !args[1])
		print_export(env_list);
	free_2d(args);
}