/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:42:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/06 16:25:37 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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

int is_valid_key(char *str)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return (1);
}

t_env_kv split_key_value(char *arg)
{
	t_env_kv kv;
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	kv.key = ft_substr(arg, 0, i);
	if (arg[i] == '=')
	{
		kv.value = ft_substr(arg, i + 1, ft_strlen(arg));
		kv.has_value = 1;
	}
	else
	{
		kv.value = NULL;
		kv.has_value = 0;
	}
	return kv;
}

int key_exist(t_env_var *env_list, char *key)
{
	t_env_var *tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

void	env_update(t_env_var *env_list, char *key, char *value)
{
	t_env_var *tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_env_back(t_env_var **env_list, t_env_var *new)
{
	t_env_var *tmp;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env_var	*create_env_var(char *key, char *value)
{
	t_env_var *new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	process_export_arg(char *arg, t_env_var **env_list)
{
	t_env_kv kv;

	kv = split_key_value(arg);
	if (*env_list && key_exist(*env_list, kv.key))
	{
		if (kv.has_value)
			env_update(*env_list, kv.key, kv.value);
	}
	else
	{
		t_env_var *new = create_env_var(kv.key, kv.value);
		add_env_back(env_list, new);
	}
	free(kv.key);
	free(kv.value);
}

void	handle_export(char **args, t_env_var **env_list)
{
	int i;

	if (!args || !args[0])
		return ;
	i = 1;
	if (!args[i])
	{
		print_export(*env_list);
		return ;
	}
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			process_export_arg(args[i], env_list);
		i++;
	}
}
