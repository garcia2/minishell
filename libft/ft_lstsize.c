/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:07:00 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/16 16:30:58 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*cur;
	int		size;

	if (lst == NULL)
		return (0);
	size = 0;
	cur = lst;
	while (cur != NULL)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}
