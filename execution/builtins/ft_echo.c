/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:11 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/10 18:36:12 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
