/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/04/27 17:36:37 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

void	ll(void)
{
	system("leaks minishell");
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int	word_count(char *s, char sep)
{
	int	i;
	int	in_word;
	int	cp;

	i = 0;
	in_word = 0;
	cp = 0;
	while (s[i])
	{
		if (s[i] == sep)
		{
			in_word = 0;
		}
		else if (s[i] != sep && in_word == 0)
		{
			in_word = 1;
			cp++;
		}
		i++;
	}
	return (cp);
}

static void	*free_arr(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**filling_arr(char c, const char *s, char **arr, int words)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (i < words)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		arr[i] = ft_substr(s, (unsigned int)start, (size_t)(end - start));
		if (!arr[i])
			return (free_arr(arr, i));
		start = end + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**splitted;

	if (!s)
		return (NULL);
	if (!*s)
	{
		splitted = (char **)malloc(sizeof(char *));
		if (!splitted)
			return (NULL);
		splitted[0] = NULL;
		return (splitted);
	}
	words = word_count((char *)s, c);
	splitted = (char **)malloc((words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	return (filling_arr(c, s, splitted, words));
}

static t_env_var	*create_node(char *env_var)
{
	t_env_var	*new_node;
	char		**split;

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
	return (new_node);
}

t_env_var	*init_env(char *envp[])
{
	t_env_var	*head;
	t_env_var	*current;
	int			i;

	if (!envp || !envp[0])
		return (NULL);
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
	return (head);
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

void	free_env_list(t_env_var *head)
{
	t_env_var	*current;
	t_env_var	*next;

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

int	main(int ac, char **av, char **envp)
{
	t_parser	*parser;
	char		*input;

	atexit(ll);
	(void)ac;
	(void)av;
	(void)envp;
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
