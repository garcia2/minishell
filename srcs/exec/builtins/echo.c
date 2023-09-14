/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:51:32 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 16:47:58 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_options(char **cmd, int i)
{
	int	j;

	j = 2;
	if (!cmd[i] || cmd[i][0] != '-' || cmd[i][1] != 'n')
		return (0);
	while (cmd[i] && cmd[i][j])
	{
		if (cmd[i][j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	echo_with_option(t_cmd_table *cmd_table, int i)
{
	int	j;

	while (check_options(cmd_table->cmd, i) == 1)
			(i)++;
	while (cmd_table->cmd[i])
	{
		j = 0;
		while (cmd_table->cmd[i][j])
		{
			write(cmd_table->outfile_fd, &cmd_table->cmd[i][j], 1);
			j++;
		}
		write(cmd_table->outfile_fd, " ", 1);
		(i)++;
	}
}

void	do_echo(t_cmd_table *cmd_table)
{
	int	i;
	int	j;

	i = 1;
	if (check_options(cmd_table->cmd, i) == 1)
		echo_with_option(cmd_table, i);
	else
	{
		while (cmd_table->cmd[i])
		{
			j = 0;
			while (cmd_table->cmd[i][j])
			{
				write(cmd_table->outfile_fd, &cmd_table->cmd[i][j], 1);
				j++;
			}
			i++;
		}
		write(cmd_table->outfile_fd, "\n", 1);
		g_error = 0;
	}
}
