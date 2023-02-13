/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:31:45 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 19:56:57 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	size_little;
	size_t	i;

	size_little = ft_strlen(little);
	if (size_little == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && (len - i >= size_little))
	{
		if (ft_strncmp(big + i, little, size_little) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
