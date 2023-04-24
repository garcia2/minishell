/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:37:45 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/05 15:48:33 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	init_here_doc(int *i, char **nb, char **temp_file_name)
{
	*i = 1;
	*nb = ft_itoa(*i++);
	*temp_file_name = ft_strjoin(".temp_file_tmp", *nb);
	if (*temp_file_name == NULL)
		return (write(1, "Error : can't create file\n", 27), 0);
	free(*nb);
	return (1);
}

t_cmd_table	*init_node(void)
{
	t_cmd_table	*new;

	new = malloc(sizeof(t_cmd_table));
	if (new == NULL)
		return (NULL);
	new->infile_fd = 0;
	new->outfile_fd = 1;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

int	is_delimiter(char *lex)
{
	if (ft_strcmp(lex, "<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">") == 0)
		return (1);
	else if (ft_strcmp(lex, "<<") == 0)
		return (1);
	else if (ft_strcmp(lex, ">>") == 0)
		return (1);
	else
		return (0);
}
