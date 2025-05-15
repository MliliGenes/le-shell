/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:04 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/15 08:20:41 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dependencies.h"

void	print_syntax_error(const char *token, const char *reason)
{
	int		stdout_save;
	char	*input;

	stdout_save = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s✗ SYNTAX ERROR %s » Token: %s%s%s » Reason: %s\n", RED, RESET,
		YELLOW, token, RESET, reason);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdout_save);
}
