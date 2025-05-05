/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/02 21:40:24 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_error(char *arg, char *message)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
}

static int	calculate_exit_status(char *arg)
{
	int	status;

	status = ft_atoi(arg) % 256;
	if (status < 0)
		status += 256;
	return (status);
}

static void	ft_exit(char **args)
{
	if (!args[1])
		exit(EXIT_SUCCESS);
	if (!is_numeric(args[1]))
	{
		print_exit_error(args[1], ": numeric argument required\n");
		exit(255);
	}
	if (args[2])
	{
		print_exit_error(NULL, "too many arguments\n");
		exit_status = 1;
		return ;
	}
	exit_status = calculate_exit_status(args[1]);
	exit(exit_status);
}

void	handle_exit(char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (args && args[0] && ft_strcmp(args[0], "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_exit(args);
	}
	free_2d(args);
}
