/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:19:35 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:47:58 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_tmp = dest;
	src_tmp = src;
	while (n > 0)
	{
		*dest_tmp = *src_tmp;
		dest_tmp++;
		src_tmp++;
		n--;
	}
	return (dest);
}
