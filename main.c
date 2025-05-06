/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/06 15:52:30 by ssbaytri         ###   ########.fr       */
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

int is_builtin(char *cmd)
{
	return (
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

int execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->cmd)
		return (1);

	if (ft_strcmp(cmd->cmd, "cd") == 0)
		handle_cd(cmd->args, shell->env);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		handle_unset(cmd->args, shell->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		handle_export(cmd->args, shell->env);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		handle_env(*shell->env);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		handle_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		handle_pwd();
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		handle_exit(cmd->args, shell);
	else
		return (1);
	return (0);
}

int excute_ast(t_ast *root, t_shell *shell)
{
	if (!root || !root->node)
		return (1);
	if (root->node->type == CMD)
	{
		t_cmd *cmd = (t_cmd *)root->node->p_token;
		if (is_builtin(cmd->cmd))
			return (excute_builtin(cmd, shell->env));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	t_parser	*parser;
	char		*input;

	(void)ac;
	(void)av;
	atexit(ll); 
	rl_bind_key('\t', rl_complete);

	shell.env = init_env_list(envp);
	shell.last_status = 0;
	shell.path = NULL;
	shell.ast = NULL;
	shell.running = 1;

	while (shell.running)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		if (*input)
			add_history(input);
		parser = parse_input(input);
		if (parser && parser->holy_tree)
		{
			shell.ast = parser->holy_tree;
			execute_ast(shell.ast, &shell);
			free_ast(parser->holy_tree);
			free_ready_tokens_list(parser->postfix_note);
			free(parser);
		}
		free(input);
	}
	return (shell.last_status);
}

