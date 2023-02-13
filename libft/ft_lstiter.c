/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:06:20 by nigarcia          #+#    #+#             */
/*   Updated: 2022/09/13 11:44:26 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	t_list	*cur;

	if (lst == NULL)
		return ;
	cur = lst;
	while (cur != NULL)
	{
		(*f)(cur->content);
		cur = cur->next;
	}
}
