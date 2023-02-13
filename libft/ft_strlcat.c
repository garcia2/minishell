/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:12:12 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:37:13 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	sized;
	size_t	i;

	i = 0;
	sized = ft_strlen(dest);
	if (sized + 1 <= size && size > 0)
	{
		while ((i + sized + 1 < size) && src[i])
		{
			dest[sized + i] = src[i];
			i++;
		}
		dest[sized + i] = '\0';
	}
	while (src[i])
		i++;
	if (sized < size)
		return (sized + i);
	else
		return (size + i);
}
