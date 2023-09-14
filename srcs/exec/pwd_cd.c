/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:33:22 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 16:46:10 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cd(t_cmd_table *cmd_table, t_env_list *env)
{
	if (ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
	{
		if (get_pwd() == 2)
			return (1);
	}
	else if (!cmd_table->cmd[1])
	{
		print_error("Error : argument required for cd\n");
		return (1);
	}
	else if (ft_strcmp(cmd_table->cmd[0], "cd") == 0 && cmd_table->cmd[2])
	{
		print_error("Minishell: cd: too many arguments\n");
		g_error = 1;
	}
	else if (!cmd_table->cmd[2] && ft_strcmp(cmd_table->cmd[0], "cd") == 0)
	{
		if (change_directory(cmd_table->cmd[1], env) == 2)
			return (1);
	}
	return (0);
}
