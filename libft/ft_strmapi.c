/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:31:21 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:22:22 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dup;

	if (s == NULL || f == NULL)
		return (NULL);
	dup = ft_strdup(s);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (dup[i])
	{
		dup[i] = (*f)(i, dup[i]);
		i++;
	}
	return (dup);
}
