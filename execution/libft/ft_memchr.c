/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:04:37 by ssbaytri          #+#    #+#             */
/*   Updated: 2024/11/01 16:46:02 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		uc;
	size_t				i;

	i = 0;
	ptr = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == uc)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
