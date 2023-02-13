/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:11:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/13 12:54:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_next_quote(char	*str, int *i)
{
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
}

static void	go_next_double_quote(char	*str, int *i)
{
	while (str[*i] != '"' && str[*i] != '\0')
		(*i)++;
}

static void	skip_white_space(char *str, int *i)
{
	while (is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
		(*i)++;
}

static void	skip_token(char *str, int *i)
{
	while (!is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
			(*i)++;
}

int	count_token(char *str)
{
	int	nb_token;
	int	i;

	nb_token = 0;
	i = 0;
	while (str[i] != '\0')
	{
		skip_white_space(str, &i);
		if (str[i] == '\'')
		{
			i++;
			go_next_quote(str, &i);
			if (str[i] == '\0')
				return (-1);
			nb_token++;
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			go_next_double_quote(str, &i);
			if (str[i] == '\0')
				return (-2);
			nb_token++;
			i++;
		}
		else if (str[i] == '$')
		{
			i++;
			if (get_env(str, &i) != NULL)
				nb_token++;
		}
		else if (str[i] != '\0')
		{
			nb_token++;
			skip_token(str, &i);
		}
	}
	return (nb_token);
}
