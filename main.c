/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/07 21:28:34 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"
#include "include/builtins.h"

void	ll(void)
{
	system("leaks -q minishell");
}

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	char	*tmp;
	char	*full_path;

	if (access(cmd->cmd, F_OK) == 0 && access(cmd->cmd, X_OK) == 0)
		return (ft_strdup(cmd->cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

char **env_to_array(t_env_var *env)
{
	int count;
	t_env_var *tmp;
	char **arr;
	
	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = env;
	count = 0;
	while (tmp)
	{
		char *joined;
		
		if (tmp->value)
		{
			joined = ft_strjoin(tmp->key, "=");
			arr[count] = ft_strjoin(joined, tmp->value);
			free(joined);
		}
		else
			arr[count] = ft_strdup(tmp->key);
		count++;
		tmp = tmp->next;
	}
	arr[count] = NULL;
	return (arr);
}

int execute_ast(t_ast *root, t_shell *shell)
{
	pid_t pid;
	int status;
	char *cmd_path;
	char **envp;
	
	if (!root || !root->node)
		return (0);
	if (root->node->type == CMD)
	{
		t_cmd *cmd = (t_cmd *)root->node->p_token;
		if (is_builtin(cmd->cmd))
			return (execute_builtin(cmd, shell));
		cmd_path = get_cmd_path(cmd, shell->path);
		if (!cmd_path)
		{
			ft_putstr_fd(cmd->cmd, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (127);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(cmd_path);
			return (1);
		}
		if (pid == 0)
		{
			envp = env_to_array(shell->env);
			execve(cmd_path, cmd->args, envp);
			perror("execve");
			free(cmd_path);
			free_2d(envp);
			exit(127);
		}
		free(cmd_path);
		waitpid(pid, &status, 0);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}
	return (0);
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

	shell.env = init_env(envp);
	shell.last_status = 0;
	shell.path = ft_split(get_env_value(shell.env, "PATH"), ':');
	if (!shell.path)
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

