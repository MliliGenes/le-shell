/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:11 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/05 23:14:23 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/builtins.h"

static void	print_echo_args(char **args, int i)
{
	int	first;

	first = 1;
	while (args[i])
	{
		if (*args[i] == '\0')
			write(STDOUT_FILENO, " ", 1);
		else
		{
			if (!first)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			first = 0;
		}
		i++;
	}
}

static int	check_n_flag(char *arg)
{
	int	j;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

void	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && check_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	print_echo_args(args, i);
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
}

void	handle_echo(char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args)
		return ;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	free_2d(args);
}
