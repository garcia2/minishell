/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:32:27 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/15 14:02:41 by nigarcia         ###   ########.fr       */
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

int	check_lexer(char **lex)
{
	if (!check_pipe(lex))
		return (printf("ERROR : PROBLEM WITH PIPE\n"), 0);
	return (1);
}
