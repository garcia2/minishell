/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:31:59 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 18:06:49 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if ((unsigned char) c == '\0')
		return ((char *)s + i + 1);
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
