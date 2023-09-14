/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:48:56 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 17:02:13 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next_quote(char	*str, int *i, char quote)
{
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
}

void	skip_white_space(char *str, int *i)
{
	while (is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
		(*i)++;
}

void	skip_token(char *str, int *i)
{
	while (!is_white_space(str[*i])
		&& !is_spec_char(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
			(*i)++;
}
