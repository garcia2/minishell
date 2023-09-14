/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_delete_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:15:20 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 16:59:47 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size_copy_checker(char *str)
{
	int	size;
	int	quote;

	quote = 0;
	if (is_quote(str[0]))
		quote++;
	if (is_quote(str[ft_strlen(str) - 1]))
		quote++;
	size = (ft_strlen(str) - quote);
	return (size);
}

char	*copy_checker(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*new_str;

	i = 0;
	j = 0;
	size = get_size_copy_checker(str);
	new_str = malloc(sizeof(char) * size + 1);
	if (new_str == NULL)
		return (NULL);
	if (is_quote(str[0]))
		i++;
	while (str[i] && i <= size)
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*copy_checker_bis(char *str)
{
	char	**tab;
	char	**t_tab;
	int		i;
	char	*new_str;

	tab = extract_quotes(str);
	t_tab = ft_calloc(get_len(tab) + 1, sizeof(char *));
	i = 0;
	while (tab[i] != NULL)
	{
		t_tab[i] = copy_checker(tab[i]);
		i++;
	}
	free_lexer(tab);
	new_str = rejoin_expand(t_tab);
	free_lexer(t_tab);
	return (new_str);
}

char	**erazer(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = copy_checker_bis(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
