/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dolars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:52:16 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/25 11:27:05 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(char *token)
{
	if (ft_strncmp(token, ">", ft_strlen(token)) == 0
		|| ft_strncmp(token, ">>", ft_strlen(token)) == 0
		|| ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (1);
	else
		return (0);
}

static int	is_limiter(char **lex, int i)
{
	if (i == 0)
		return (0);
	if (ft_strncmp(lex[i - 1], "<<", ft_strlen(lex[i - 1])) == 0)
		return (1);
	else
		return (0);
}

static int	convert_dolars_process(char **lex, int i)
{
	char	*temp_str;

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
			return (free(temp_str), 0);
		free(lex[i]);
		lex[i] = temp_str;
	}
	return (1);
}

int	convert_dolars(char **lex)
{
	int		i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (convert_dolars_process(lex, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
