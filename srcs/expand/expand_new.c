/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:46:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 10:53:15 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexers(char ***lexers)
{
	int	i;

	if (lexers == NULL)
		return ;
	i = 0;
	while (lexers[i] != NULL)
	{
		free_lexer(lexers[i]);
		i++;
	}
	free(lexers);
}

int	get_str_nb_part(char *str)
{
	int		nb_part;
	int		i;

	nb_part = 0;
	i = 0;
	while (str[i] != '\0')
	{	
		nb_part++;
		if (is_quote(str[i]))
		{
			i++;
			go_next_quote(str, &i, str[i - 1]);
			i++;
		}
		else
			skip_token(str, &i);
	}
	return (nb_part);
}

static int	str_next_part_len(char *str, int i)
{
	int		len;
	char	quote;

	if (is_quote(str[i]))
	{
		quote = str[i];
		len = 1;
		while (str[i + len] != '\0' && str[i + len] != quote)
			len++;
		len++;
	}
	else
	{
		len = 0;
		while (str[i + len] != '\0' && !is_quote(str[i + len]))
			len++;
	}
	return (len);
}

static char	**expand_split_part(char *str)
{
	char	**split;
	int		len;
	int		i;
	int		j;

	split = ft_calloc(get_str_nb_part(str) + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		len = str_next_part_len(str, i);
		printf("len = %d, i = %d\n", len, i);
		split[j] = ft_calloc(len + 1, sizeof(char));
		if (split[j] == NULL)
			return (free_lexer(split), NULL);
		ft_strlcpy(split[j], str + i, len + 1);
		printf("part %d = [%s]\n", j, split[j]);
		i += len;
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	*get_expanded_str(char *str, t_env_list *env)
{
	char	*expanded_str;

	if (str[0] != '\'')
		expanded_str = replace_env_var(str, env);
	else
		expanded_str = ft_strdup(str);
	return (expanded_str);
}

char	**get_expanded_lex(char *str, t_env_list *env)
{
	char	**expanded_lex;
	char	**expanded_lex2;
	//char	*expanded_str;
	//int		i;

	expanded_lex = expand_split_part(str);
	print_lexer(expanded_lex);
	printf("EXPAND\n");
	expanded_lex2 = relexing(expanded_lex, env);
	free_lexer(expanded_lex);
	print_lexer(expanded_lex2);
	return (expanded_lex2);
}

static int	lex_len(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
		i++;
	return (i);
}

void	print_lexers(char ***lexers)
{
	int	i;

	i = 0;
	while (lexers[i] != NULL)
	{
		printf("PRINT OF Lexers[%d]\n", i);
		print_lexer(lexers[i]);
		i++;
	}
}

int		get_nb_elem_lexers(char ***lexers)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (lexers[i] != NULL)
	{
		j = 0;
		while (lexers[i][j] != NULL)
		{
			j++;
			len++;
		}
		i++;
	}
	return (len);
}

char	**rejoin_lexers(char ***lexers)
{
	char	**joined_lex;
	int		x;
	int		i;
	int		j;

	printf("nb_elem = %d\n", get_nb_elem_lexers(lexers));
	joined_lex = ft_calloc(get_nb_elem_lexers(lexers), sizeof(char *));
	x = 0;
	i = 0;
	while (lexers[i] != NULL)
	{
		j = 0;
		while (lexers[i][j] != NULL)
		{
			printf("copy of [%s]\n", lexers[i][j]);
			joined_lex[x] = ft_strdup(lexers[i][j]);
			j++;
			x++;
		}
		i++;
	}
	joined_lex[x] = NULL;
	return (joined_lex);
}

char	**relexing(char **lex, t_env_list *env)
{
	char	***lexers;
	int		i;

	lexers = ft_calloc(lex_len(lex) + 1, sizeof(char **));
	if (lexers == NULL)
		return (NULL);
	i = 0;
	while (lex[i] != NULL)
	{
		if (lex[i][0] == '"')
		{
			expand_cmd(lex + i, env);
			lexers[i] = ft_calloc(2, sizeof(char *));
			lexers[i][0] = ft_strdup(lex[i]);
			lexers[i][1] = NULL;
		}
		else if (lex[i][0] == '\'')
		{
			lexers[i] = ft_calloc(2, sizeof(char *));
			lexers[i][0] = ft_calloc(ft_strlen(lex[i] + 1), sizeof(char));
			ft_strlcpy(lexers[i][0], lex[i], ft_strlen(lex[i]) + 1);
			lexers[i][1] = NULL;
		}
		else
		{
			expand_cmd(lex + i, env);
			printf("expand = [%s]\n", lex[i]);
			lexers[i] = ft_split(lex[i], ' ');//lexer(lex[i]);
		}
		i++;
	}
	lexers[i] = NULL;
	printf("done\n");
	return (rejoin_lexers(lexers));
}

// int	nb_lex(char **lex, t_env_list *env)
// {
// 	int		i;
// 	int		nb_lex;

// 	i = 0;
// 	while (lex[i] != NULL)
// 	{
// 		lexers[i] = get_expanded_lex(lex[i], env);
// 		i++;
// 	}
// }

void	expand_new(char ***lex_ptr, t_env_list *env)
{
	char	***lexers;
	char	**expanded_lex;
	int		i;

	lexers = ft_calloc(lex_len(*lex_ptr) + 1, sizeof(char **));
	i = 0;
	while ((*lex_ptr)[i] != NULL)
	{
		//printf("nb part of [%s] = %d\n", (*lex_ptr)[i], get_str_nb_part((*lex_ptr)[i]));
		lexers[i] = get_expanded_lex((*lex_ptr)[i], env);
		i++;
	}
	lexers[i] = NULL;
	printf("this is the end\n");
	print_lexers(lexers);
	expanded_lex = rejoin_lexers(lexers);
	print_lexer(expanded_lex);
	free_lexers(lexers);
	//free_lexer(*lex_ptr);
	*lex_ptr = expanded_lex;
}
