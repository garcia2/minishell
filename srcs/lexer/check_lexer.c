/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:32:27 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/13 11:38:16 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (ft_strcmp(lex[i], "|") == 0)
		{
			if (i == 0 || lex[i + 1] == NULL)
				return (0);
			if (ft_strcmp(lex[i + 1], "|") == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_delimiters(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (is_delimiter(lex[i]))
		{
			if (lex[i + 1] == NULL
				|| is_delimiter(lex[i + 1])
				|| ft_strcmp(lex[i + 1], "|") == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_lexer(char **lex)
{
	if (!check_pipe(lex))
		return (print_error("ERROR : PROBLEM WITH PIPE\n"), 0);
	if (!check_delimiters(lex))
		return (print_error("ERROR : PROBLEM WITH DELIMITERS\n"), 0);
	return (1);
}
