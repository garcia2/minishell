/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:29:47 by nigarcia          #+#    #+#             */
/*   Updated: 2023/01/17 21:07:42 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_word(char const *s, char c)
{
	int	i;
	int	words;

	words = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (s[0] != c)
		words++;
	i = 1;
	while (s[i])
	{
		if ((s[i] != c) && (s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static int	len_next_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**empty_malloc(void)
{
	char	**split;

	split = malloc(sizeof(char *));
	split[0] = NULL;
	return (split);
}

static char	**critical_free(char **split, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		j;

	j = 0;
	if (s == NULL || ft_strlen(s) == 0)
		return (empty_malloc());
	split = malloc(sizeof(char *) * ((nb_word(s, c) + 1)));
	if (split == NULL)
		return (NULL);
	if (s[0] != c)
		split[j++] = ft_substr(s, 0, len_next_word(s, c));
	if (j == 1 && split[0] == NULL)
		return (critical_free(split, j - 1));
	while (*(++s))
	{
		if ((*s != c) && (*(s - 1) == c))
		{
			split[j++] = ft_substr(s, 0, len_next_word(s, c));
			if (split[j - 1] == NULL)
				return (critical_free(split, j - 1));
		}
	}
	split[j] = NULL;
	return (split);
}
