/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:11:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/15 14:28:21 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(char *str, int *i, int	*nb_token)
{
	skip_white_space(str, i);
	if ((str[*i] == '\'') || (str[*i] == '"'))
	{
		(*i)++;
		go_next_quote(str, i, str[(*i) - 1]);
		if (str[*i] == '\0')
			return (-1);
		(*i)++;
		if (str[*i] == '\0' || is_white_space(str[*i]) || str[*i] == '|')
			(*nb_token)++;
	}
	else if (str[*i] == '|')
	{
		(*i)++;
		(*nb_token)++;
	}
	else if (str[*i] != '\0')
	{
		skip_token(str, i);
		if (str[*i] == '\0' || is_white_space(str[*i]) || str[*i] == '|')
			(*nb_token)++;
	}
	return (0);
}

int	count_token(char *str)
{
	int	nb_token;
	int	i;
	int	res;

	nb_token = 0;
	i = 0;
	while (str[i] != '\0')
	{
		res = process(str, &i, &nb_token);
		if (res != 0)
			return (res);
	}
	return (nb_token);
}
