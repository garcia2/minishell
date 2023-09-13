/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:58:48 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/13 11:38:03 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_part(char *str)
{
	int		i;
	int		nb_part;

	nb_part = 0;
	i = 0;
	while (str[i] != '\0')
	{
		nb_part++;
		if (str[i] == '\'' || str[i] == '"')
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

char	*copy_part(int i, int len, char *str)
{
	char	*copy;

	copy = ft_calloc(len + 1, sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, str + i, len + 1);
	return (copy);
}

int	split_part(char *str, char **split)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i;
			i++;
			go_next_quote(str, &i, str[i - 1]);
			i++;
		}
		else
		{
			j = i;
			skip_token(str, &i);
		}
		*split = copy_part(j, i - j, str);
		if (*split == NULL)
			return (0);
		split++;
	}
	return (1);
}

char	**get_part(char *str)
{
	int		nb_part;
	char	**split;

	nb_part = count_part(str);
	if (nb_part == 0)
		return (NULL);
	split = ft_calloc(nb_part + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	split[nb_part] = NULL;
	if (split_part(str, split) == 0)
		return (free_lexer(split), NULL);
	return (split);
}

int	expand_cmd(char **str_ptr, t_env_list *env)
{
	char	**split;
	char	*join;

	split = get_part(*str_ptr);
	if (split == NULL)
		return (0);
	convert_dolars(split, env);
	join = join_split(split);
	free_lexer(split);
	if (join == NULL)
		return (0);
	free(*str_ptr);
	*str_ptr = join;
	return (1);
}
