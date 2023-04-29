/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:16:08 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/29 11:10:55 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pid(t_pipex *pipex, int pid)
{
	pipex->rfd = pid - 1;
	pipex->wfd = pid;
	if (pid == 0)
		pipex->rfd = -1;
	if (pid == pipex->nb_cmd - 1)
		pipex->wfd = -1;
	close_pipes_not_used(pipex);
	if (pid == 0)
		pipex->rdup = -1;
	else
		pipex->rdup = dup2(pipex->pipes[pipex->rfd][0], 0);
	if (pid == pipex->nb_cmd - 1)
		pipex->wdup = -1;
	else
		pipex->wdup = dup2(pipex->pipes[pipex->wfd][1], 1);
	if (pid != 0)
		close(pipex->pipes[pipex->rfd][0]);
	if (pid != pipex->nb_cmd - 1)
		close(pipex->pipes[pipex->wfd][1]);
}

int	ft_dup(t_pipex *pipex, int pid)
{
	dup_pid(pipex, pid);
	return (1);
}
