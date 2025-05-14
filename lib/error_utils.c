/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:04 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/12 18:30:20 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dependencies.h"

void	print_syntax_error(const char *token, const char *reason)
{
	printf("%s✗ SYNTAX ERROR %s » Token: %s%s%s » Reason: %s\n", RED, RESET,
		YELLOW, token, RESET, reason);
		
}
