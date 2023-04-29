/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:03:06 by nico              #+#    #+#             */
/*   Updated: 2023/04/24 13:13:20 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * nb_pipes);
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			return (free_pipes(pipes, nb_pipes), NULL);
		if (pipe(pipes[i]) == -1)
			return (free_pipes(pipes, nb_pipes), NULL);
		i++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int nb_pipes)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < nb_pipes)
	{
		if (pipes[i] != NULL)
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_pipes_not_used(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		if (i != pipex->rfd)
			close(pipex->pipes[i][0]);
		if (i != pipex->wfd)
			close(pipex->pipes[i][1]);
		i++;
	}
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}
