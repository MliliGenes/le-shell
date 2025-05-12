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

// void ll()
// {
// 	system("leaks -q minishell");
// }

int	execute_ast(t_shell *shell)
{
	t_ast	*root;

	root = shell->parser->holy_tree;
	if (!root)
		return (1);
	if (root->node->type == CMD)
		execute_command(root->node->p_token, shell);
	// else if (root->node->type == OP)
	// {
	// 	if (((t_op *)root->node->p_token)->type == OP_PIPE)
	// 		return (handle_pipe());
	// 	if (((t_op *)root->node->p_token)->type == OP_AND)
	// 		return (handle_and());
	// 	if (((t_op *)root->node->p_token)->type == OP_OR)
	// 		return (handle_or());
	// }
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)ac;
	(void)av;
	// atexit(ll);
	rl_bind_key('\t', rl_complete);
	shell.env = init_env(envp);
	shell.last_status = 0;
	shell.path = ft_split(get_env_value(shell.env, "PATH"), ':');
	shell.parser = NULL;
	shell.running = 1;
	while (shell.running)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		shell.parser = parse_input(input);
		if (shell.parser && shell.parser->holy_tree)
		{
			execute_ast(&shell);
			free_ast(shell.parser->holy_tree);
			free_ready_tokens_list(shell.parser->postfix_note);
			free(shell.parser);
		}
		free(input);
	}
	free(input);
	free_env_list(shell.env);
	free_2d(shell.path);
	return (shell.last_status);
}
