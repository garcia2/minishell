/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:06:56 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/05 17:18:56 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(char **lex)
{
	int	i;

	if (lex == NULL)
		return ;
	i = 0;
	while (lex[i] != NULL)
	{
		free(lex[i]);
		i++;
	}
	free(lex);
}

void	print_lexer(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		printf("lex[%d]=[%s]\n", i, lex[i]);
		i++;
	}
}

char	**get_empty_lexer(void)
{
	char	**empty_lex;

	empty_lex = ft_calloc(1, sizeof(char *));
	if (empty_lex == NULL)
		return (NULL);
	empty_lex[0] = NULL;
	return (empty_lex);
}

char	**lexer(char *str)
{
	char	**lex;
	int		nb_token;

	nb_token = count_token(str);
	if (nb_token < 0)
		return (print_error("ERROR : PROBLEM WITH COUNT_TOKEN\n")
			, NULL);
	lex = ft_calloc(nb_token + 1, sizeof(char *));
	if (lex == NULL)
		return (print_error("ERROR : PROBLEM WITH MALLOC OF LEX\n")
			, NULL);
	if (split_lexer(lex, str) == 0)
		return (print_error("ERROR : PROBLEM WITH SPLIT_LEXER\n"),
			free_lexer(lex), NULL);
	if (check_lexer(lex) == 0)
		return (free_lexer(lex), get_empty_lexer());
	return (lex);
}
