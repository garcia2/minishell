/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_space_without_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:01:50 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 16:57:21 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_spaces_process(char *str, char quote, int is_in_quote)
{
	int	i;
	int	nb_spaces;

	nb_spaces = str[0] != ' ';
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i - 1] == ' ' && !is_in_quote)
			nb_spaces++;
		if (is_quote(str[i]))
		{
			if (is_in_quote && str[i] == quote)
				is_in_quote = 0;
			else if (!is_in_quote)
			{
				is_in_quote = 1;
				quote = str[i];
			}
		}
		i++;
	}
	return (nb_spaces);
}

int	get_nb_spaces_without_quotes(char *str)
{
	int	is_in_quote;
	int	quote;
	int	nb_spaces;

	quote = 'o';
	if (ft_strlen(str) == 0)
		return (0);
	is_in_quote = 0;
	if (is_quote(str[0]))
	{
		is_in_quote = 1;
		quote = str[0];
	}
	nb_spaces = get_nb_spaces_process(str, quote, is_in_quote);
	return (nb_spaces);
}

static int	get_len_process(char *str, int i, int is_in_quote, char quote)
{
	int	j;

	j = 1;
	while (str[i + j] != '\0')
	{
		if (str[i + j] == ' ' && !is_in_quote)
			return (j);
		else if (is_quote(str[i + j]))
		{
			if (is_in_quote && str[i + j] == quote)
				is_in_quote = 0;
			else if (!is_in_quote)
			{
				is_in_quote = 1;
				quote = str[i];
			}
		}
		j++;
	}
	return (j);
}

int	get_len_next_word(char *str, int i)
{
	int		is_in_quote;
	char	quote;
	int		len;

	if (str[i] == '\0')
		return (0);
	quote = 'o';
	is_in_quote = 0;
	if (is_quote(str[i]))
	{
		is_in_quote = 1;
		quote = str[i];
	}
	len = get_len_process(str, i, is_in_quote, quote);
	return (len);
}

char	**split_spaces_witout_quotes(char *str)
{
	char	**splited_tab;
	int		i;
	int		len;
	int		k;

	splited_tab = ft_calloc(get_nb_spaces_without_quotes(str) + 1,
			sizeof(char *));
	k = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] == ' ')
			i++;
		len = get_len_next_word(str, i);
		splited_tab[k] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(splited_tab[k], str + i, len + 1);
		splited_tab[k][len] = '\0';
		k++;
		i += len;
	}
	splited_tab[k] = NULL;
	return (splited_tab);
}
