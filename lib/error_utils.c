/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:04 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 21:54:20 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	print_syntax_error(char *token, char *reason)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("✗ SYNTAX ERROR ", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd("» Token: ", STDERR_FILENO);
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(" » Reason: ", STDERR_FILENO);
	ft_putstr_fd(reason, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
