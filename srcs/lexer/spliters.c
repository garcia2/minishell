/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:36:37 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/17 14:19:48 by nicolas          ###   ########.fr       */
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
	split = ft_calloc(len + 1, sizeof(char));
	if (split == NULL)
		return (NULL);
	ft_strlcpy(split, str + *i, len + 1);
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
	split = ft_calloc(len + 1, sizeof(char));
	if (split == NULL)
		return (NULL);
	ft_strlcpy(split, str + *i, len + 1);
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
