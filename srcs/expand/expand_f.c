/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:08:41 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/12 17:18:08 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_process(char *str, t_env_list *env)
{
	char	**tab;
	char	**tab2;
	char	*new_str;

	tab = extract_quotes(str);
	tab2 = extract_dollars_tab(tab, env);
	free_lexer(tab);
	tab = interpret_dolars(tab2, env);
	new_str = rejoin_expand(tab);
	free_lexer(tab);
	tab = split_spaces_witout_quotes(new_str);
	free(new_str);
	tab2 = erazer(tab);
	free_lexer(tab);
	return (tab2);
}

int	sizer(char **tab)
{
	int		i;
	int		j;
	int		malloc_len;
	char	**t_tab;

	malloc_len = 0;
	i = 0;
	while (tab[i])
	{
		t_tab = extract_quotes(tab[i]);
		j = 0;
		while (t_tab[j])
		{
			malloc_len++;
			j++;
		}
		free_lexer(t_tab);
		i++;
	}
	return (malloc_len);
}

char	**expands(char **tab, t_env_list *env)
{
	int		i;
	int		j;
	int		k;
	char	**t_tab;
	char	**new_tab;

	i = -1;
	k = 0;
	new_tab = malloc(sizeof(char *) * (sizer(tab) + 1));
	if (new_tab == NULL)
		return (0);
	while (tab[++i])
	{
		t_tab = expand_process(tab[i], env);
		j = -1;
		while (t_tab[++j])
		{
			new_tab[k] = strdup(t_tab[j]);
			k++;
		}
		free_lexer(t_tab);
	}
	new_tab[k] = NULL;
	return (new_tab);
}
