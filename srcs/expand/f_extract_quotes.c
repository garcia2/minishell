/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_extract_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:47:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 16:57:07 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str)
{
	int		nb_quotes;
	char	quote;
	int		i;

	i = 0;
	nb_quotes = 0;
	while (str[i] != '\0')
	{
		nb_quotes++;
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] != '\0' && str[i] != quote)
				i++;
			i += str[i] == quote;
		}
		else
		{
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '"')
				i++;
		}
	}
	return (nb_quotes);
}

static int	split_quotes_process(char *str, int i)
{
	int		j;
	char	quote;

	j = 1;
	if (str[i] == '\'' || str[i] == '"')
	{
		quote = str[i];
		while (str[i + j] != '\0' && str[i + j] != quote)
			j++;
		j += str[i + j] == quote;
	}
	else
	{
		while (str[i + j] != '\0' && str[i + j] != '\''
			&& str[i + j] != '"')
			j++;
	}
	return (j);
}

static void	split_quotes(char **splited_quotes, char *str)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = split_quotes_process(str, i);
		splited_quotes[k] = ft_calloc(j + 1, sizeof(char));
		ft_strlcpy(splited_quotes[k], str + i, j + 1);
		splited_quotes[k][j] = '\0';
		k++;
		i += j;
	}
	splited_quotes[k] = NULL;
}

char	**extract_quotes(char *str)
{
	char	**splited_quotes;

	splited_quotes = ft_calloc(count_quotes(str) + 1, sizeof(char *));
	if (splited_quotes == NULL)
		return (NULL);
	split_quotes(splited_quotes, str);
	return (splited_quotes);
}
