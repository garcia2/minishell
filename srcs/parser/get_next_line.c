/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:12:07 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/30 12:12:35 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	*buffer;

	i = 0;
	rd = 0;
	buffer = malloc(sizeof(char) * 1000);
	if (BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	while (1)
	{
		rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
		if (rd <= 0)
			break ;
		buffer[i++] = character;
		if (character == '\n')
			break ;
	}
	if ((!buffer[i - 1] && !rd) || rd == -1)
		return (free(buffer), NULL);
	buffer[i] = '\0';
	return (buffer);
}
