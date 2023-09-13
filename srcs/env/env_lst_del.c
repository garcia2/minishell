/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:35:28 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 18:26:47 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*env_lst_pop(t_env_list **lst, char *key)
{
	t_env_list	*pop;
	t_env_list	*cur;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	if (ft_strcmp((*lst)->key, key) == 0)
	{
		pop = *lst;
		*lst = (*lst)->next;
		pop->next = NULL;
		return (pop);
	}
	cur = *lst;
	while (cur->next != NULL)
	{
		if (ft_strcmp(cur->next->key, key) == 0)
		{
			pop = cur->next;
			cur->next = cur->next->next;
			pop->next = NULL;
			return (pop);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	env_lst_clear(t_env_list **lst)
{
	t_env_list	*cur;

	if (*lst == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		cur = (*lst)->next;
		env_lst_free_one(*lst);
		*lst = cur;
	}
	env_lst_free_one(*lst);
	*lst = NULL;
}

void	env_lst_free_one(t_env_list *lst)
{
	if (lst == NULL)
		return ;
	if (lst->key != NULL)
		free(lst->key);
	if (lst->value != NULL)
		free(lst->value);
	lst->next = NULL;
	free(lst);
}
