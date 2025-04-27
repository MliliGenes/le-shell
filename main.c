/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/27 16:42:51 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks minishell");
}

static t_env_var *create_node(char *env_var)
{
	t_env_var *new_node;
	char **split;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	split = ft_split(env_var, '=');
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

t_env_var	*init_env(char *envp[])
{
	t_env_var *head;
	t_env_var *current;
	int i;

	if (!envp || !envp[0])
		return NULL;
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


int	main(void)
{
	t_parser	*parser;
	char		*input;

	atexit(ll);
	rl_bind_key('\t', rl_complete);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		parser = parse_input(input);
		if (parser && parser->holy_tree)
			print_ast_simple(parser->holy_tree);
		free_ast(parser->holy_tree);
		free_ready_tokens_list(parser->postfix_note);
		free(parser);
		free(input);
		input = NULL;
	}
	return (0);
}
