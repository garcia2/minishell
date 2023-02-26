/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:23:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/26 11:24:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_print(t_env_list *lst)
{
	while (lst != NULL)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
