/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:18:27 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/29 17:29:23 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_split_total_len(char **split)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (split[i] != NULL)
	{
		len += ft_strlen(split[i]);
		i++;
	}
	return (len);
}

char	*join_split(char **split)
{
	char	*join_str;
	int		i;
	int		j;

	join_str = ft_calloc(get_split_total_len(split) + 1, sizeof(char));
	if (join_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (split[i] != NULL)
	{
		ft_strlcpy(join_str + j, split[i], ft_strlen(split[i]) + 1);
		j += ft_strlen(split[i]);
		i++;
	}
	return (join_str);
}
