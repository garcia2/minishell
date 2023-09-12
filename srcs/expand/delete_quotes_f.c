/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:15:20 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/12 16:59:25 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_checker(char *str)
{
	int		i;
	int		j;
	int		size;
	int		quote;
	char	*new_str;

	i = 0;
	j = 0;
	quote = 0;
	if (is_quote(str[0]))
		quote++;
	if (is_quote(str[strlen(str) - 1]))
		quote++;
	size = (strlen(str) - quote);
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

// char	**erazer(char **tab)
// {
// 	int		i;
// 	char	**new_tab;

// 	i = 0;
// 	while (tab[i])
// 		i++;
// 	new_tab = malloc(sizeof(char *) * (i + 1));
// 	if (new_tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		new_tab[i] = copy_checker(tab[i]);
// 		i++;
// 	}
// 	new_tab[i] = NULL;
// 	free_lexer(tab);
// 	return (new_tab);
// }

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

	(void) env;
	i = -1;
	k = 0;
	new_tab = malloc(sizeof(char *) * (sizer(tab) + 1));
	if (new_tab == NULL)
		return (0);
	while (tab[++i])
	{
		t_tab = extract_quotes(tab[i]);
		j = -1;
		while (t_tab[++j])
		{
			new_tab[k] = strdup(t_tab[j]);
			k++;
		}
		free_lexer(t_tab);
	}
	new_tab[k] = NULL;
	print_lexer(new_tab);
	return (erazer(new_tab));
}
