/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:35:56 by sel-mlil Â         #+#    #+#             */
/*   Updated: 2025/05/08 18:54:31 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"
#include "include/parsing.h"
#include "include/signals.h"

int	execute_ast_node(t_ast *node, t_shell *shell)
{
	t_op	*op;

	if (!node)
		return (1);
	if (node->node->type == CMD)
		return (execute_command((t_cmd *)node->node->p_token, shell));
	else if (node->node->type == OP)
	{
		op = (t_op *)node->node->p_token;
		if (op->type == OP_PIPE)
			return (handle_pipe(node, shell));
		else if (op->type == OP_AND)
			return (handle_and(node, shell));
		else if (op->type == OP_OR)
			return (handle_or(node, shell));
	}
	return (1);
}

int	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		return (1);
	shell->last_status = 0;
	shell->path = ft_split(get_env_value(shell->env, "PATH"), ':');
	shell->parser = NULL;
	shell->running = 1;
	return (0);
}

void	cleanup_iteration(t_shell *shell)
{
	if (shell->parser)
	{
		if (shell->parser->holy_tree)
			free_ast(shell->parser->holy_tree);
		if (shell->parser->postfix_note)
			free_ready_tokens_list(shell->parser->postfix_note);
		free(shell->parser);
		shell->parser = NULL;
	}
	if (shell->input)
		free(shell->input);
}

char* prompt_stderr(const char* prompt) {
    int stdout_save = dup(STDOUT_FILENO);
    dup2(STDERR_FILENO, STDOUT_FILENO);
    char* input = readline(prompt);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdout_save);
    return input;
}

void	shell_loop(t_shell *shell)
{
	setup_signals();
	rl_bind_key('\t', rl_complete);
	while (shell->running)
	{
		shell->input = prompt_stderr(PROMPT);
		if (!shell->input)
		{
			printf("exit\n");
			break ;
		}
		if (*shell->input)
		{
			add_history(shell->input);
			shell->parser = parse_input(shell->input);
			if (shell->parser && shell->parser->holy_tree)
				shell->last_status = execute_ast_node(shell->parser->holy_tree,shell);
			else
				shell->last_status = 2;
		}
		cleanup_iteration(shell);
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		free_env_list(shell->env);
	if (shell->path)
		free_2d(shell->path);
}

int	main(int ac, char **av, char **envp)
{
	t_shell shell;

	(void)ac;
	(void)av;
	if (init_shell(&shell, envp) != 0)
		return (1);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_status);
}
