/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:28:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/24 14:26:31 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_process(t_pipex *pipex, t_cmd_table *cmd_table, t_env_list *env)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] < 0)
			return (2);
		if (pipex->pids[i] == 0)
		{
			if (exec_pipex_command(pipex, i, cmd_table, env) != 0)
				return (0);
			return (1);
		}
		i++;
		cmd_table = cmd_table->next;
	}
	close_all_pipes(pipex);
	return (waitforit(pipex));
}
