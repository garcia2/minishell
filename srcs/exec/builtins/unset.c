/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:13:25 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/13 22:35:33 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_env_list **env, char	**args)
{
	int			i;
	t_env_list	*pop;

	i = 0;
	while (args[i] != NULL)
	{
		pop = env_lst_pop(env, args[i]);
		env_lst_print(pop);
		env_lst_clear(&pop);
		i++;
	}
	return (1);
}
