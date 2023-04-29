/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:17:35 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/27 09:59:34 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_cmd(char **cmds)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (cmds[nb_cmd] != NULL)
		nb_cmd++;
	return (nb_cmd);
}

int	get_lexers_nb_cmd(char ***lexs)
{
	int	nb_cmd;
	int	i;

	nb_cmd = 0;
	i = 0;
	while (lexs[i] != NULL)
	{
		nb_cmd += get_nb_cmd(lexs[i]);
		i++;
	}
	return (nb_cmd);
}
