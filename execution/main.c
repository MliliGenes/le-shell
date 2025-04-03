/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:02:50 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/03 20:49:18 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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


void hadnle_exit(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
}

int ft_echo(char **args)
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
    return (0);
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

void	handle_cd(char **args)
{
	//TODO: hanlde cd with relative paths and absolute paths
	//TODO: Before calling chdir(), store the current PWD as OLDPWD (since OLDPWD should always point
	// TODO: Call chdir() with the new path (whether it's absolute or constructed from a relative path).
	//TODO: After chdir(), update PWD by calling getcwd() to get the new current directory and setting it as PWD.
}

void	handle_env(char *input, char **env)
{
	if (ft_strcmp(input, "env") == 0)
	{
		int i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	return;
}

void ll()
{
	system("leaks minishell");
}

int main(int argc, char *argv[], char *envp[])
{
	atexit(ll);
	
	char *input;
	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		if (ft_strlen(input) > 0 && input)
		{
			add_history(input);
			handle_echo(input);
			handle_pwd(input);
			handle_env(input, envp);
			hadnle_exit(input);
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}