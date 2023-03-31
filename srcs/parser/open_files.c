/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:22:25 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/31 12:39:53 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd_opened(int fd)
{
	if (fd > 2)
		close(fd);
}

void	open_infile(int *fd, char *file_name)
{
	check_fd_opened(*fd);
	*fd = open(file_name, O_RDONLY);
}

void	open_outfile(int *fd, char *file_name)
{
	check_fd_opened(*fd);
	*fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	open_append(int *fd, char *file_name)
{
	check_fd_opened(*fd);
	*fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
}