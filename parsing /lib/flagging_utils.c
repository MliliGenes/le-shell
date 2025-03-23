/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagging_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:32:50 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/03/23 17:07:31 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

int	is_and_op(char *src)
{
	if (ft_strlen(src) < 2)
		return (-1);
	return ((src[0] == '&' && src[1] == '&'));
}

int	is_or_op(char *src)
{
	if (ft_strlen(src) < 2)
		return (-1);
	return ((src[0] == '|' && src[1] == '|'));
}

int	is_pipe_op(char *src)
{
	return ((src[0] == '|'));
}

int	is_redir_in(char *src)
{
	return (src[0] == '<');
}

int	is_redir_out(char *src)
{
	return (src[0] == '>');
}

int	is_redir_her(char *src)
{
	if (ft_strlen(src) < 2)
		return (-1);
	return (src[0] == '<' && src[1] == '<');
}

int	is_redir_append(char *src)
{
	if (ft_strlen(src) < 2)
		return (-1);
	return (src[0] == '>' && src[1] == '>');
}
