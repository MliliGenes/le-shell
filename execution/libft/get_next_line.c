/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:44:58 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/01 21:36:51 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(int fd, char *dumpstr)
{
	int		bytes_read;
	char	*buffer;

	if (!dumpstr)
		dumpstr = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(dumpstr), dumpstr = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), buffer = NULL, free(dumpstr), dumpstr = NULL,
				NULL);
		buffer[bytes_read] = '\0';
		dumpstr = ft_strjoin1(dumpstr, buffer);
		if (!dumpstr)
			return (free(buffer), buffer = NULL, NULL);
		if (ft_strchr(dumpstr, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, dumpstr);
}

char	*ft_get_line(char *dumpstr)
{
	char	*line;
	int		i;

	i = 0;
	if (!dumpstr || !dumpstr[0])
		return (NULL);
	while (dumpstr[i] && dumpstr[i] != '\n')
		i++;
	if (dumpstr[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (dumpstr[i] && dumpstr[i] != '\n')
	{
		line[i] = dumpstr[i];
		i++;
	}
	if (dumpstr[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_recycle_dumpstr(char *dumpstr)
{
	char	*new_dumpstr;
	int		i;
	int		j;

	i = 0;
	while (dumpstr[i] && dumpstr[i] != '\n')
		i++;
	if (!dumpstr[i])
		return (free(dumpstr), dumpstr = NULL, NULL);
	i++;
	new_dumpstr = malloc(sizeof(char) * (ft_strlen(dumpstr) - i + 1));
	if (!new_dumpstr)
		return (free(dumpstr), dumpstr = NULL, NULL);
	j = 0;
	while (dumpstr[i])
		new_dumpstr[j++] = dumpstr[i++];
	new_dumpstr[j] = '\0';
	return (free(dumpstr), dumpstr = NULL, new_dumpstr);
}

char	*get_next_line(int fd)
{
	static char	*dumpstr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(dumpstr), dumpstr = NULL, NULL);
	dumpstr = ft_read_file(fd, dumpstr);
	if (!dumpstr)
		return (free(dumpstr), dumpstr = NULL, NULL);
	line = ft_get_line(dumpstr);
	if (!line)
		return (free(dumpstr), dumpstr = NULL, NULL);
	dumpstr = ft_recycle_dumpstr(dumpstr);
	return (line);
}
