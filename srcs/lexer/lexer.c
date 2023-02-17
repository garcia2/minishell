/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:06:56 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/17 14:26:00 by nicolas          ###   ########.fr       */
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

static int	process(char **lex, char *str, int *lex_i, int *str_i)
{
	skip_white_space(str, str_i);
	if (str[*str_i] == '\'')
	{
		lex[*lex_i] = split_with_simple_quotes(str, str_i);
		if (lex[*lex_i] == NULL)
			return (0);
		(*lex_i)++;
	}
	else if (str[*str_i] == '"')
	{
		lex[*lex_i] = split_with_double_quotes(str, str_i);
		if (lex[*lex_i] == NULL)
			return (0);
		(*lex_i)++;
	}
	else if (str[*str_i] != '\0')
	{
		lex[*lex_i] = split_without_quotes(str, str_i);
		if (lex[*lex_i] == NULL)
			return (0);
		(*lex_i)++;
	}
	return (1);
}

static int	split_lexer(char **lex, char *str)
{
	int	str_i;
	int	lex_i;

	str_i = 0;
	lex_i = 0;
	while (str[str_i] != '\0')
	{
		if (process(lex, str, &lex_i, &str_i) == 0)
			return (0);
	}
	return (1);
}

void	print_lexer(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
	{
		printf("lex[%d]='%s'\n", i, lex[i]);
		i++;
	}
}

char	**lexer(char *str)
{
	char	**lex;
	int		nb_token;

	nb_token = count_token(str);
	if (nb_token <= 0)
		return (NULL);
	lex = ft_calloc(nb_token + 1, sizeof(char *));
	if (lex == NULL)
		return (NULL);
	if (split_lexer(lex, str) == 0)
		return (free_lexer(lex), NULL);
	lex[nb_token] = NULL;
	return (lex);
}
