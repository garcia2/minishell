/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:29:17 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/24 10:38:06 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		result[10];
	int			size;
	long int	long_n;

	long_n = n;
	if (long_n < 0)
	{
		long_n *= -1;
		ft_putchar_fd('-', fd);
	}
	size = 0;
	while (long_n > 9)
	{
		result[size++] = '0' + (long_n % 10);
		long_n /= 10;
	}
	result[size] = '0' + (long_n % 10);
	while (size >= 0)
		ft_putchar_fd(result[size--], fd);
}
