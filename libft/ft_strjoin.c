/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:30:28 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 17:29:42 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	lens1;
	size_t	lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	join = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, lens1 + 1);
	ft_strlcat(join, s2, lens1 + lens2 + 1);
	return (join);
}
