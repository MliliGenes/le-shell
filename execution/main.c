/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:02:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/02 00:10:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exit_status = 0;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ll(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	char		*expand_input;
	t_env_var	*env_list;

	atexit(ll);
	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	handle_signals();
	while (1)
	{
		input = readline("minishell> ");
		expand_input = expand_exit_status(input);
		add_history(input);
		if (!expand_input)
		{
			printf("exit\n");
			rl_clear_history();
			free(input);
			break ;
		}
		if (ft_strlen(expand_input) > 0 && expand_input)
			exec_builtins(expand_input, &env_list);
		free(expand_input);
		free(input);
	}
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
