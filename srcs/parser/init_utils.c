/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:37:45 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/31 01:10:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

t_cmd_table	*lstlast(t_cmd_table *lst)
{
	t_cmd_table	*cur;

	if (lst == NULL)
		return (NULL);
	cur = lst;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	add_back(t_cmd_table **lst, t_cmd_table *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lstlast(*lst)->next = new;
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
