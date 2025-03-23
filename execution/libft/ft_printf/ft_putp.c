/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:51:15 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/01 22:08:46 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_p(void *addr)
{
	unsigned long	address;
	char			*hex;
	int				i;
	int				j;

	address = (unsigned long)addr;
	i = 0;
	hex = "0123456789abcdef";
	if (address >= 16)
		i += ft_put_p((void *)(address / 16));
	j = address % 16;
	i += ft_putchar(hex[j]);
	return (i);
}
