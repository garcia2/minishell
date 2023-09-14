/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env_by_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:05:27 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 17:02:26 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_by_key(t_env_list *env_lst, char *key)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

/*
* Return 1 on success, 0 if no key found, -1 on malloc problem
*/
int	set_env_by_key(t_env_list *env_lst, char *key, char *new_value)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(new_value);
			if (env_lst->value == NULL)
				return (-1);
			else
				return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}
