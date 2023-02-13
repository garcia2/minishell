/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:35:38 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:40:24 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s);
	dup = ft_calloc(size + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, size + 1);
	return (dup);
}
