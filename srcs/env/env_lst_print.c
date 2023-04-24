/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:23:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 14:33:09 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_print(t_env_list *lst)
{
	while (lst != NULL)
	{
		if (lst->value != NULL)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
