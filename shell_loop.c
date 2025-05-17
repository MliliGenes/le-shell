/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:46:30 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/17 16:49:44 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"
#include "include/parsing.h"
#include "include/signals.h"

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

char	*prompt_stderr(const char *prompt)
{
	int		stdout_save;
	char	*input;

	stdout_save = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	input = readline(prompt);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdout_save);
	return (input);
}

void	shell_loop(t_shell *shell)
{
	int	status;

	setup_signals();
	while (shell->running)
	{
		shell->input = prompt_stderr(PROMPT);
		if (!shell->input)
			break ;
		if (*shell->input)
		{
			add_history(shell->input);
			shell->parser = parse_input(shell->input);
			if (shell->parser && shell->parser->holy_tree)
			{
				status = open_here_docs(shell->parser->postfix_note);
				if (status)
				{
					cleanup_iteration(shell);
					shell->last_status = status;
					continue ;
				}
				shell->last_status = execute_ast_node(shell->parser->holy_tree,
						shell);
			}
			else
				shell->last_status = 2;
		}
		cleanup_iteration(shell);
		if (!shell->running)
			break ;
	}
}
