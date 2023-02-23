/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:36:37 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/23 17:28:32 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_with_simple_quotes(char *str, int *i)
{
	char	*split;
	int		len;

	(*i)++;
	len = 0;
	while (str[(*i) + len] != '\'' && str[(*i) + len] != '\0')
		len++;
	split = ft_calloc(len + 3, sizeof(char));
	if (split == NULL)
		return (NULL);
	ft_strlcpy(split + 1, str + *i, len + 1);
	split[0] = '\'';
	split[len + 1] = '\'';
	(*i) += (len + 1);
	return (split);
}

char	*split_with_double_quotes(char *str, int *i)
{
	char	*split;
	int		len;

	(*i)++;
	len = 0;
	while (str[(*i) + len] != '"' && str[(*i) + len] != '\0')
		len++;
	split = ft_calloc(len + 3, sizeof(char));
	if (split == NULL)
		return (NULL);
	ft_strlcpy(split + 1, str + *i, len + 1);
	split[0] = '"';
	split[len + 1] = '"';
	(*i) += (len + 1);
	return (split);
}

char	*split_without_quotes(char *str, int *i)
{
	char	*split;
	int		len;

	len = 0;
	while (!is_white_space(str[(*i) + len])
		&& str[(*i) + len] != '\''
		&& str[(*i) + len] != '"'
		&& str[(*i) + len] != '\0')
		len++;
	split = ft_calloc(len + 1, sizeof(char));
	if (split == NULL)
		return (NULL);
	ft_strlcpy(split, str + *i, len + 1);
	(*i) += len;
	return (split);
}
