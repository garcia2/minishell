/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:19:39 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/24 14:38:48 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	result[10];
	int		size;
	int		i;	

	size = 0;
	while (n > 9)
	{
		result[size++] = '0' + (n % 10);
		n /= 10;
	}
	i = size;
	result[i] = '0' + (n % 10);
	while (i >= 0)
		ft_putchar_fd(result[i--], fd);
	return (size + 1);
}

int	ft_printf_u(unsigned int n)
{
	return (ft_putunbr_fd(n, 1));
}
