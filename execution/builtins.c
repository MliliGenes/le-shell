/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:11:12 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/10 16:49:08 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_pwd(char *input)
{
	char *pwd;
	
	if ((ft_strcmp(input, "pwd") == 0))
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
			printf("%s\n", pwd);
		else
			perror("getcwd");
		free(pwd);
	}
}

static void ft_echo(char **args)
{
	int i = 1;
    int n_flag = 0;
    int first = 1;

    while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
    {
        int j = 2;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] == '\0')
        {
            n_flag = 1;
            i++;
        }
        else
            break;
    }

    while (args[i])
    {
        if (*args[i] == '\0')
            write(1, " ", 1);
        else
        {
            if (!first)
                write(1, " ", 1);
            write(1, args[i], ft_strlen(args[i]));
            first = 0;
        }
        i++;
    }

    if (!n_flag)
        write(1, "\n", 1);
}

void	handle_echo(char *input)
{
	char **args;
	
	args = ft_split(input, ' ');
	{
		if (ft_strncmp(args[0], "echo", 4) == 0)
			ft_echo(args);
	}
	free_2d(args);
}

static int is_numeric(char *str)
{
    int i = 0;
    if (!str || !*str)
        return 0;
    if (str[0] == '+' || str[0] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

void handle_exit(char *input)
{
    char **args;

    args = ft_split(input, ' ');
    if (args && args[0] && ft_strcmp(args[0], "exit") == 0)
    {
        ft_putstr_fd("exit\n", 1);
        if (!args[1])
            exit(0);
        if (!is_numeric(args[1]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            free_2d(args);
            exit(255);
        }
        if (args[2])
        {
            exit_status = 1;
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
            free_2d(args);
            return;
        }
        exit_status = ft_atoi(args[1]) % 256;
        if (exit_status < 0)
            exit_status += 256;
        free_2d(args);
        exit(exit_status);
    }
    free_2d(args);
}

