/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_interpret_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:24:23 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 23:25:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char **tab)
{
	int	len;

	len = 0;
	while (tab[len] != NULL)
		len++;
	return (len);
}

char	**interpret_dolars(char **tab, t_env_list *env)
{
	char	**new_tab;
	int		i;

	new_tab = ft_calloc(get_len(tab) + 1, sizeof(char *));
	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '\'')
			new_tab[i] = ft_strdup(tab[i]);
		else
			new_tab[i] = replace_env_var(tab[i], env);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
