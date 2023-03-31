/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:18:36 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/31 12:18:46 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*lstlast(t_cmd_table *lst)
{
	t_cmd_table	*cur;

	if (lst == NULL)
		return (NULL);
	cur = lst;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	add_back(t_cmd_table **lst, t_cmd_table *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lstlast(*lst)->next = new;
}
