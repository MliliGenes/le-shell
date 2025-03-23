/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:51:03 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/03/01 22:08:11 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	helper_func(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_put_un(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1);
	else if (c == 'p')
		count += ft_putstr("0x") + ft_put_p(va_arg(args, void *));
	else if (c == '%')
		count += ft_putchar('%');
	else
		count += ft_putchar('%') + ft_putchar(c);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (write(1, NULL, 0) == -1 || !format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			count += helper_func(format[i], args);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
