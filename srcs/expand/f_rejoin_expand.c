/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_rejoin_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:39:28 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/13 11:36:06 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	get_total_len(char **tab)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		total_len += ft_strlen(tab[i]);
		i++;
	}
	return (total_len);
}

char	*rejoin_expand(char **tab)
{
	char	*str;
	int		i;
	int		k;

	str = ft_calloc(get_total_len(tab) + 1, sizeof(char));
	k = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		ft_strlcpy(str + k, tab[i], ft_strlen(tab[i]) + 1);
		k += ft_strlen(tab[i]);
		i++;
	}
	str[k] = '\0';
	return (str);
}
