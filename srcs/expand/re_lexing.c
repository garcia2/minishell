/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:23:52 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/08 14:12:58 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**re_lexing_cmd_with_quotes(char *cmd)
{
	char	**lex;

	lex = ft_calloc(2, sizeof(char *));
	if (lex == NULL)
		return (0);
	lex[0] = ft_strdup(cmd);
	if (lex[0] == NULL)
		return (0);
	lex[1] = NULL;
	return (lex);
}

void	free_lexers(char ***lexs)
{
	int	i;

	if (lexs == NULL)
		return ;
	i = 0;
	while (lexs[i] != NULL)
	{
		free_lexer(lexs[i]);
		i++;
	}
	free(lexs);
}

char	***get_lexers(char **cmds, int *quote_map)
{
	int		i;
	char	***lexs;

	lexs = ft_calloc(get_nb_cmd(cmds) + 1, sizeof(char **));
	if (lexs == NULL)
		return (NULL);
	i = 0;
	while (cmds[i] != NULL)
	{
		if (quote_map[i] == 0)
			lexs[i] = lexer(cmds[i]);
		else
			lexs[i] = re_lexing_cmd_with_quotes(cmds[i]);
		if (lexs[i] == NULL)
			return (free_lexers(lexs), NULL);
		i++;
	}
	lexs[i] = NULL;
	return (lexs);
}

char	**join_lexers(char ***lexs)
{
	char	**lex;
	int		i;
	int		j;
	int		k;

	lex = ft_calloc(get_lexers_nb_cmd(lexs) + 1, sizeof(char *));
	if (lex == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (lexs[i] != NULL)
	{
		j = 0;
		while (lexs[i][j] != NULL)
		{
			lex[k] = ft_strdup(lexs[i][j]);
			if (lex[k] == NULL)
				return (free_lexer(lex), NULL);
			k++;
			j++;
		}
		i++;
	}
	lex[k] = NULL;
	return (lex);
}

int	re_lexing_cmd(char ***cmds, int *quote_map)
{
	char	***lexs;
	char	**joined_lexs;

	lexs = get_lexers(*cmds, quote_map);
	if (lexs == NULL)
		return (0);
	// int	i = 0;
	// while (lexs[i] != NULL)
	// {
	// 	printf("\nprint_lex[%d]\n", i);
	// 	print_lexer(lexs[i]);
	// 	i++;
	// }
	joined_lexs = join_lexers(lexs);
	if (joined_lexs == NULL)
		return (free_lexers(lexs), 0);
	free(*cmds);
	*cmds = joined_lexs;
	//printf("final lexing\n");
	//print_lexer(joined_lexs);
	return (1);
}
