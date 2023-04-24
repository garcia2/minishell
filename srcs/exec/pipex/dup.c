/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:16:08 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/24 15:44:00 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	dup_reader(t_pipex *pipex, char *file_in)
// {
// 	int	fd_file_in;

// 	fd_file_in = open(file_in, O_RDONLY);
// 	if (fd_file_in < 0)
// 		return (close_all_pipes(pipex), 0);
// 	pipex->rfd = pipex->nb_cmd - 1;
// 	pipex->wfd = 0;
// 	close_pipes_not_used(pipex);
// 	pipex->rdup = dup2(fd_file_in, 0);
// 	pipex->wdup = dup2(pipex->pipes[pipex->wfd][1], 1);
// 	close(fd_file_in);
// 	close(pipex->pipes[pipex->rfd][0]);
// 	close(pipex->pipes[pipex->wfd][1]);
// 	return (1);
// }

// int	dup_writer(t_pipex *pipex, char *file_out)
// {
// 	int	fd_file_out;

// 	fd_file_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd_file_out < 0)
// 		return (close_all_pipes(pipex), 0);
// 	pipex->rfd = pipex->nb_cmd - 2;
// 	pipex->wfd = 0;
// 	close_pipes_not_used(pipex);
// 	pipex->rdup = dup2(pipex->pipes[pipex->rfd][0], 0);
// 	pipex->wdup = dup2(fd_file_out, 1);
// 	close(fd_file_out);
// 	close(pipex->pipes[pipex->rfd][0]);
// 	close(pipex->pipes[pipex->wfd][1]);
// 	return (1);
// }

void	dup_pid(t_pipex *pipex, int pid)
{
	pipex->rfd = pid - 1;
	pipex->wfd = pid;
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
	// if (pid == 0)
	// {
	// 	if (dup_reader(pipex, argv[1]) == 0)
	// 		return (print_infile_error(argv[1]), 0);
	// }
	// else if (pid == pipex->nb_cmd - 1)
	// {
	// 	if (dup_writer(pipex, argv[pipex->nb_cmd + 2]) == 0)
	// 		return (print_infile_error(argv[pipex->nb_cmd + 2]), 0);
	// }
	// else
	dup_pid(pipex, pid);
	return (1);
}
