/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:16:34 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/04 13:32:30 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_tab_line(t_env_list *env)
{
	char	*env_tab_line;
	char	*cur;

	cur = ft_strjoin(env->key, "=");
	if (cur == NULL)
		return (NULL);
	env_tab_line = ft_strjoin(cur, env->value);
	free(cur);
	return (env_tab_line);
}

char	**get_env_tab(t_env_list *env)
{
	char	**env_tab;
	int		i;

	if (env == NULL)
		return (NULL);
	env_tab = ft_calloc(env_lst_size(env) + 1, sizeof(char *));
	if (env_tab == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			env_tab[i] = get_env_tab_line(env);
			if (env_tab[i] == NULL)
				return (free_lexer(env_tab), NULL);
			i++;
		}
		env = env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
