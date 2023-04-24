/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:33:22 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/24 09:36:53 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cd(t_cmd_table *cmd_table, t_env_list *env)
{
	if (!cmd_table->cmd[1] && ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
	{
		if (get_pwd() == 2)
			return (2);
	}
	else if (!cmd_table->cmd[2] && ft_strcmp(cmd_table->cmd[0], "cd") == 0)
	{
		if (change_directory(cmd_table->cmd[1], env) == 2)
			return (2);
	}
	return (0);
}
