/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:46:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/02 13:16:47 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//printf("len = %d, i = %d\n", len, i);
		split[j] = ft_calloc(len + 1, sizeof(char));
		if (split[j] == NULL)
			return (free_lexer(split), NULL);
		ft_strlcpy(split[j], str + i, len + 1);
		//printf("part %d = [%s]\n", j, split[j]);
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
	//char	*expanded_str;
	//int		i;

	expanded_lex = expand_split_part(str);
	print_lexer(expanded_lex);
	relexing(expanded_lex, env);
	/*i = 0;
	while (expanded_lex[i] != NULL)
	{
		expanded_str = get_expanded_str(expanded_lex[i], env);
		free(expanded_lex[i]);
		expanded_lex[i] = expanded_str;
		i++;
	}*/
	//print_lexer(expanded_lex);
	return (NULL);
}

static int	lex_len(char **lex)
{
	int	i;

	i = 0;
	while (lex[i] != NULL)
		i++;
	return (i);
}

char	***relexing(char **lex, t_env_list *env)
{
	char	***lexers;
	int		i;
	int		j;

	printf("Starting relexing\n");
	lexers = ft_calloc(lex_len(lex), sizeof(char **));
	if (lexers == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (lex[i] != NULL)
	{
		if (lex[i][0] == '"')
		{
			expand_cmd(lex + i, env);
			printf("[%s] has double quotes\n", lex[i]);
		}
		else if (lex[i][0] == '\'')
			printf("[%s] has simple quotes\n", lex[i]);
		else
		{
			expand_cmd(lex + i, env);
			printf("[%s] has no quotes\n", lex[i]);
		}
		i++;
	}
	return (lexers);
}

char	**expand_new(char **lex, t_env_list *env)
{
	char	***lexers;
	int		i;

	(void) lexers;
	i = 0;
	while (lex[i] != NULL)
	{
		printf("nb part of [%s] = %d\n", lex[i], get_str_nb_part(lex[i]));
		get_expanded_lex(lex[i], env);
		i++;
	}
	return (NULL);
}
