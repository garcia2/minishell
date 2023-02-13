/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:24:37 by nico              #+#    #+#             */
/*   Updated: 2022/05/24 14:32:19 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_fd(unsigned long long int n, char *base, int fd)
{
	char	result[16];
	int		size;
	int		i;

	size = 0;
	while (n > 15)
	{
		result[size++] = base[n % 16];
		n /= 16;
	}
	result[size] = base[n % 16];
	i = size;
	while (i >= 0)
		ft_putchar_fd(result[i--], fd);
	return (size + 1);
}

int	ft_printf_p(unsigned long long ptr)
{
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (ft_puthex_fd(ptr, "0123456789abcdef", 1) + 2);
}

int	ft_printf_x(int n, char type)
{
	char	*base;

	if (type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	else
		return (0);
	return (ft_puthex_fd((unsigned int)n, base, 1));
}
