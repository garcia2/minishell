/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:42:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/01 12:49:24 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_exists(t_env_list *lst, char *key)
{
	while (lst != NULL)
	{
		if (ft_strcmp(lst->key, key) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	env_lst_size(t_env_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	env_lst_add_back(t_env_list **lst, t_env_list *new)
{
	if (new == NULL)
		return ;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	env_lstlast(*lst)->next = new;
}

t_env_list	*env_lstlast(t_env_list *lst)
{
	t_env_list	*cur;

	if (lst == NULL)
		return (NULL);
	cur = lst;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

t_env_list	*env_lstnew(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	if (key != NULL)
	{
		new->key = ft_strdup(key);
		if (new->key == NULL)
			return (env_lst_clear(&new), NULL);
	}
	if (value != NULL)
	{
		new->value = ft_strdup(value);
		if (new->key == NULL)
			return (env_lst_clear(&new), NULL);
	}
	new->next = NULL;
	return (new);
}
