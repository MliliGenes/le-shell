/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:02:52 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/27 23:45:50 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **split_env_var(char *arg)
{
	char **split;
	int i;

	i = 0;
	split = malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	split[0] = ft_substr(arg, 0, i);
	if (arg[i] == '=')
		split[1] = ft_substr(arg, i + 1, ft_strlen(arg));
	else
		split[1] = NULL;
	split[2] = NULL;
	return (split);
}

static t_env_var *create_node(char *env_var)
{
	t_env_var *new_node;
	char **split;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	split = split_env_var(env_var);
	if (!split)
	{
		free(new_node);
		return (NULL);
	}
	new_node->key = ft_strdup(split[0]);
	if (split[1])
		new_node->value = ft_strdup(split[1]);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	free_2d(split);
	return (new_node);
}

t_env_var	*handle_empty_env()
{
	t_env_var *head;
	char *cwd;

	head = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
		add_env_back(&head, create_env_var("PWD", cwd));
	add_env_back(&head, create_env_var("OLDPWD", NULL));
	add_env_back(&head, create_env_var("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"));
	free(cwd);
	return (head);
}

t_env_var	*init_env(char *envp[])
{
	t_env_var *head;
	t_env_var *current;
	int i;

	if (!envp || !envp[0])
		return handle_empty_env();
	head = NULL;
	i = 0;
	head = create_node(envp[i++]);
	current = head;
	while (envp[i])
	{
		current->next = create_node(envp[i]);
		current = current->next;
		i++;
	}
	return head;
}

static void	print_env(t_env_var *env)
{
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void free_env_list(t_env_var *head)
{
    t_env_var *current;
    t_env_var *next;
    
    current = head;
    while (current)
    {
        next = current->next;
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}

void	handle_env(char *input, t_env_var *env)
{
	if (ft_strcmp(input, "env") == 0)
	{
		if (env)
			print_env(env);
	}
}
