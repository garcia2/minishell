/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:33:16 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/30 12:12:20 by jileroux         ###   ########.fr       */
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

size_t	ft_stringlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	write_in_file(char *limiter, int fd, char *readed_line)
{
	int		size;
	char	*limit;

	size = ft_strlen(limiter) + 2;
	limit = malloc(sizeof(char) * size);
	limit = ft_strcpy(limit, limiter);
	while (1)
	{
		write (STDIN_FILENO, ">>", 2);
		readed_line = get_next_line(STDIN_FILENO);
		if (compare_eof(readed_line, limit) == 0)
		{
			free(limit);
			free(readed_line);
			break ;
		}
		write (fd, readed_line, ft_stringlen(readed_line));
		free(readed_line);
	}
	return (1);
}

int	here_doc_logic(t_cmd_table *cmd_table, char *limiter)
{
	int		i;
	int		fd;
	char	*temp_file_name;
	char	*readed_line;

	i = 1;
	readed_line = NULL;
	temp_file_name = ft_strjoin(".temp_file_tmp", ft_itoa(i));
	while (access(temp_file_name, R_OK) == 0)
	{
		free(temp_file_name);
		i++;
		temp_file_name = ft_strjoin(".temp_file_tmp", ft_itoa(i));
	}
	fd = open(temp_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write_in_file(limiter, fd, readed_line) == 0)
		return (0);
	close (fd);
	fd = open(temp_file_name, O_RDONLY);
	cmd_table->infile_fd = fd;
	return (0);
}
