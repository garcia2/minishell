/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:01:17 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/08 14:17:11 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_quote_map(char **lex)
{
	int	i;
	int	*quote_map;

	quote_map = ft_calloc(get_nb_cmd(lex) + 1, sizeof(int));
	if (quote_map == NULL)
		return (NULL);
	i = 0;
	while (lex[i] != NULL)
	{
		quote_map[i] = is_quote(lex[i][0]);
		i++;
	}
	quote_map[i] = -1;
	return (quote_map);
}

