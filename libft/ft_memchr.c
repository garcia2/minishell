/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:26:44 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:49:19 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tab;
	unsigned char		uc;
	size_t				i;

	tab = s;
	uc = c;
	i = 0;
	while (i < n)
	{
		if (tab[i] == uc)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
