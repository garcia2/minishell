/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_extract_dollars_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:34:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 16:56:44 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_dollars_tab_without_quote(char **new_tab, char *str, int *k)
{
	char	**temp_tab;
	int		i;

	temp_tab = extract_dollars(str);
	i = 0;
	while (temp_tab[i] != NULL)
	{
		new_tab[*k] = ft_strdup(temp_tab[i]);
		i++;
		(*k)++;
	}
	free_lexer(temp_tab);
}

int	extract_dollars_tab_process(char **tab)
{
	int	i;
	int	nb_dollars;

	nb_dollars = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		if (!is_quote(tab[i][0]))
			nb_dollars += get_nb_dollars(tab[i]);
		else
			nb_dollars++;
		i++;
	}
	return (nb_dollars);
}

char	**extract_dollars_tab(char **tab)
{
	char	**new_tab;
	int		nb_dollars;
	int		i;
	int		k;

	nb_dollars = extract_dollars_tab_process(tab);
	new_tab = ft_calloc(nb_dollars + 2, sizeof(char *));
	i = 0;
	k = 0;
	while (tab[i] != NULL)
	{
		if (!is_quote(tab[i][0]))
			extract_dollars_tab_without_quote(new_tab, tab[i], &k);
		else
		{
			new_tab[k] = ft_strdup(tab[i]);
			k++;
		}
		i++;
	}
	new_tab[k] = NULL;
	return (new_tab);
}
