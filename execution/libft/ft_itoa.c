/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:19:06 by ssbaytri          #+#    #+#             */
/*   Updated: 2024/11/02 13:49:23 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	fill_res(int n, char *res, int len)
{
	if (n == INT_MIN)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
	}
	else if (n == 0)
	{
		res[0] = '0';
		return ;
	}
	else if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		res[len--] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	i = num_len(n);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	res[i--] = '\0';
	fill_res(n, res, i);
	return (res);
}
