/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:58:21 by nigarcia          #+#    #+#             */
/*   Updated: 2022/11/18 17:15:48 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*cur;

	if (*lst == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		cur = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = cur;
	}
	ft_lstdelone(*lst);
	*lst = NULL;
}
