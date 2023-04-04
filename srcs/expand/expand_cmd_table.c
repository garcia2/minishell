/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:12:27 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/31 17:21:00 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_table(t_cmd_table *cmd_tab, t_env_list *env)
{
	int	i;

	i = 0;
	while (cmd_tab->cmd[i] != NULL)
	{
		expand_cmd(&(cmd_tab->cmd[i]), env);
		i++;
	}
}

void	expand_cmd_tables(t_cmd_table *cmd_tab, t_env_list *env)
{
	while (cmd_tab != NULL)
	{
		expand_cmd_table(cmd_tab, env);
		cmd_tab = cmd_tab->next;
	}
}