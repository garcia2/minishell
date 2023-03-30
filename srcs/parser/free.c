/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:40:06 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/01 15:26:51 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(t_cmd_table *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return ;
	if (lst->infile)
		free(lst->infile);
	if (lst->outfile)
		free(lst->outfile);
	if (lst->here_doc)
		free(lst->here_doc);
	while (lst->cmd && lst->cmd[i])
	{
		free(lst->cmd[i]);
		i++;
	}
	if (lst->cmd)
		free(lst->cmd);
	free(lst);
}

void	clear_lst(t_cmd_table **lst)
{
	t_cmd_table	*cur;

	if (*lst == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		cur = (*lst)->next;
		del_lst(*lst);
		*lst = cur;
	}
	del_lst(*lst);
	*lst = NULL;
}
