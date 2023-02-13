/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:26:19 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/12 09:59:28 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	get_decimal_size(long int n)
{
	int	size;

	size = 1;
	while (n > 9)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			size;
	long int	long_n;

	long_n = n;
	if (long_n < 0)
		long_n *= -1;
	size = get_decimal_size(long_n);
	if (n < 0)
		size++;
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	result[size--] = '\0';
	while (long_n > 9)
	{
		result[size--] = '0' + (long_n % 10);
		long_n /= 10;
	}
	result[size] = '0' + (long_n % 10);
	return (result);
}
