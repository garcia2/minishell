/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:11:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/13 17:00:40 by nicolas          ###   ########.fr       */
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
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]));
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		go_next_double_quote(str, i);
		if (str[*i] == '\0')
			return (-2);
		(*i)++;
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]));
	}
	else if (str[*i] != '\0')
	{
		skip_token(str, i);
		(*nb_token) += (str[*i] == '\0' || is_white_space(str[*i]));
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
