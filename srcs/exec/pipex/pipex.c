/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:28:40 by nico              #+#    #+#             */
/*   Updated: 2023/09/13 12:59:50 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*get_pipex(int nb_cmd)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	pipex->nb_cmd = nb_cmd;
	pipex->pipes = get_pipes(nb_cmd);
	if (pipex->pipes == NULL)
		return (free_pipex(pipex), NULL);
	pipex->pids = (int *)malloc(sizeof(int) * (nb_cmd));
	if (pipex->pids == NULL)
		return (free_pipex(pipex), NULL);
	return (pipex);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	if (pipex->pipes != NULL)
		free_pipes(pipex->pipes, pipex->nb_cmd);
	if (pipex->pids != NULL)
		free(pipex->pids);
	free(pipex);
}

void	close_pipex_dup(t_pipex *pipex)
{
	check_fd_closed(pipex->rdup);
	check_fd_closed(pipex->wdup);
}
