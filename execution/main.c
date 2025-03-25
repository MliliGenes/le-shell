/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:02:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/25 05:58:28 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		write(1, "\nminishell> ", 12);
}

int exec_builtins(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	return 1;
}

void ll()
{
	system("leaks minishell");
}

int main()
{
	// atexit(ll);
	
	char *input;
	
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		exec_builtins(input);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(input) > 0)
			printf("%s\n", input);
		free(input);
	}
	return (0);
}