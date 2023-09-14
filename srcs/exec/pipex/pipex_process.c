/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:28:39 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 15:18:41 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_process(t_pipex *pipex, t_cmd_table *cmd_table, t_env_list **env)
{
	t_cmd_table	*save_cmd_table;

	save_cmd_table = cmd_table;
	pipex->pid = 0;
	while (pipex->pid < pipex->nb_cmd)
	{
		pipex->pids[pipex->pid] = fork();
		if (pipex->pids[pipex->pid] < 0)
			return (2);
		if (pipex->pids[pipex->pid] == 0)
		{
			if (exec_ppx_cmd(pipex, cmd_table, env, save_cmd_table) != 0)
				return (0);
			return (1);
		}
		check_fd_closed(cmd_table->infile_fd);
		check_fd_closed(cmd_table->outfile_fd);
		(pipex->pid)++;
		cmd_table = cmd_table->next;
	}
	close_all_pipes(pipex);
	return (waitforit(pipex));
}
