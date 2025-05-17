/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 05:24:36 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/16 07:33:35 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	refill_buffer(int fd, char *buffer, int *b_read, int *b_pos)
{
	if (*b_pos >= *b_read)
	{
		*b_read = read(fd, buffer, BUFFER_SIZE);
		*b_pos = 0;
		if (*b_read < 0)
			return (-1);
		if (*b_read == 0)
			return (0);
	}
	return (1);
}
char	*get_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	b_read;
	static int	b_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1337)
	{
		if (b_pos >= b_read)
		{
			b_read = read(fd, buffer, BUFFER_SIZE);
			b_pos = 0;
			if (b_read <= 0)
				break ;
		}
		line[i++] = buffer[b_pos++];
		if (buffer[b_pos - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
