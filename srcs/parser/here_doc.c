/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:16 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/04 15:12:57 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_eof(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\n';
	i++;
	dest[i] = '\0';
	return (dest);
}

int	write_in_file(char *limiter, int fd, char *readed_line)
{
	int		size;
	char	*limit;

	size = ft_strlen(limiter) + 2;
	limit = malloc(sizeof(char) * size);
	// a proteger
	limit = ft_strcpy(limit, limiter);
	while (1)
	{
		write (STDIN_FILENO, ">", 1);
		readed_line = get_next_line(STDIN_FILENO);
		if (compare_eof(readed_line, limit) == 0)
		{
			free(limit);
			free(readed_line);
			break ;
		}
		write (fd, readed_line, ft_strlen(readed_line));
		free(readed_line);
	}
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

int	here_doc_logic(t_cmd_table *cmd_table, char *limiter)
{
	int		i;
	int		fd;
	char	*temp_file_name;
	char	*readed_line;
	char	*nb;

	i = 1;
	readed_line = NULL;
	nb = ft_itoa(i);
	temp_file_name = ft_strjoin(".temp_file_tmp", nb);
	// a proteger
	free(nb);
	while (access(temp_file_name, R_OK) == 0)
	{
		free(temp_file_name);
		i++;
		nb = ft_itoa(i);
		temp_file_name = ft_strjoin(".temp_file_tmp", nb);
		// a proteger
		free(nb);
	}
	fd = open(temp_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write_in_file(limiter, fd, readed_line) == 0)
		return (0);
	fd_gestion(cmd_table, fd, temp_file_name);
	return (1);
}
