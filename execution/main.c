/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:02:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/10 18:38:36 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void ll()
{
	system("leaks minishell");
}

int main(int argc, char *argv[], char *envp[])
{
	atexit(ll);
	char *input;
	char *expand_input;
	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		expand_input = expand_exit_status(input);
		if (!expand_input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		if (ft_strlen(expand_input) > 0 && expand_input)
			exec_builtins(expand_input);
		free(expand_input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
