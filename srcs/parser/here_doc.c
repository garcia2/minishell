/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:16 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 20:35:47 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_signal(char *readed_line, int fd_dup, int fd)
{
	if (g_error == 42)
	{
		free(readed_line);
		dup2(fd_dup, STDIN_FILENO);
		close(fd_dup);
		return (close(fd), 0);
	}
	return (1);
}

int	write_in_file(char *limiter, int fd, char *readed_line)
{
	int		fd_dup;

	fd_dup = dup(STDIN_FILENO);
	signal(SIGINT, &signal_heredoc);
	while (1 && g_error != 42)
	{
		readed_line = readline(">");
		if (check_signal(readed_line, fd_dup, fd) == 0)
			return (init_signal(), close(fd_dup), 0);
		if (!readed_line)
			break ;
		if (ft_strcmp(readed_line, limiter) == 0)
		{
			free(readed_line);
			break ;
		}
		write (fd, readed_line, ft_strlen(readed_line));
		write (fd, "\n", 1);
		free(readed_line);
	}
	close(fd_dup);
	return (1);
}

void	fd_gestion(t_cmd_table *cmd_table, int fd, char *temp_file_name)
{
	close (fd);
	fd = open(temp_file_name, O_RDONLY);
	check_fd_opened(cmd_table->infile_fd);
	cmd_table->infile_fd = fd;
	free(temp_file_name);
}

int	here_doc_ctrlc(char *temp_file_name)
{
	free(temp_file_name);
	printf("\n");
	return (0);
}

int	here_doc_logic(t_cmd_table *cmd_table, char *limiter)
{
	int		i;
	int		fd;
	char	*temp_file_name;
	char	*readed_line;
	char	*nb;

	readed_line = NULL;
	nb = NULL;
	temp_file_name = NULL;
	init_here_doc(&i, &nb, &temp_file_name);
	while (access(temp_file_name, R_OK) == 0)
	{
		free(temp_file_name);
		nb = ft_itoa(i++);
		temp_file_name = ft_strjoin(".temp_file_tmp", nb);
		if (temp_file_name == NULL)
			return (free(nb), write(1, "Error : can't create file\n", 27), 0);
		free(nb);
	}
	fd = open(temp_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write_in_file(limiter, fd, readed_line) == 0)
		return (close(fd), here_doc_ctrlc(temp_file_name));
	fd_gestion(cmd_table, fd, temp_file_name);
	return (1);
}
