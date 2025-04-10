/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:28 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/04/10 18:36:35 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
