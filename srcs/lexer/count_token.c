/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:11:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/14 14:26:51 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(char *str, int *i, int	*nb_token)
{
	skip_white_space(str, i);
	if (str[*i] == '\'')
	{
		(*i)++;
		go_next_quote(str, i);
		if (str[*i] == '\0')
			return (-1);
		(*i)++;
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]) || str[*i] == '|');
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		go_next_double_quote(str, i);
		if (str[*i] == '\0')
			return (-2);
		(*i)++;
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]) || str[*i] == '|');
	}
	else if (str[*i] == '|')
	{
		if (str[*i + 1] == '\0')
			return (-3);
		(*i)++;
		(*nb_token)++;
	}
	else if (str[*i] != '\0')
	{
		skip_token(str, i);
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]) || str[*i] == '|');
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
