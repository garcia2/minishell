/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:06:56 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/23 19:01:54 by nigarcia         ###   ########.fr       */
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

int	is_redirection(char *token)
{
	if (ft_strncmp(token, ">", ft_strlen(token)) == 0
	|| ft_strncmp(token, ">>", ft_strlen(token)) == 0
	|| ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (1);
	else
		return (0);
}

int is_limiter(char **lex, int i)
{
	if (i == 0)
		return (0);
	printf("diff de %s = %d\n" , lex[i - 1], ft_strncmp(lex[i - 1], "<<", ft_strlen(lex[i - 1]) == 0));
	if (ft_strncmp(lex[i - 1], "<<", ft_strlen(lex[i - 1]) == 0))
	{
		return (1);
	}
	else
		return (0);
}

int	convert_dolars(char **lex)
{
	int		i;
	char	*temp_str;

	i = 0;
	while (lex[i] != NULL)
	{
		printf("i = %d\n", i);
		if (lex[i][0] == '\"')
		{
			temp_str = replace_env_var(lex[i]);
			if (temp_str == NULL)
				return (0);
			free(lex[i]);
			lex[i] = temp_str;
		}
		else if (lex[i][0] != '\'' && !is_limiter(lex, i))
		{
			temp_str = replace_env_var(lex[i]);
			if (temp_str == NULL)
				return (0);
			if (ft_strlen(temp_str) == 0
			&& (i != 0 && is_redirection(lex[i - 1])))
				return (0);
			free(lex[i]);
			lex[i] = temp_str;
		}
		i++;
	}
	return (1);
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
	convert_dolars(lex);
	return (lex);
}
