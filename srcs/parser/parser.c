/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:31:53 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/22 15:13:10 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*init_table(char **lex)
{
	int			i;
	t_cmd_table	*cmd_table;
	t_cmd_table	*tmp;

	i = 0;
	cmd_table = NULL;
	while (lex[i])
	{
		tmp = init_node();
		if (tmp == NULL)
			return (NULL);
		init_redir(lex, tmp, &i);
		if (lex[i])
			i++;
		add_back(&cmd_table, tmp);
	}
	return (cmd_table);
}

t_cmd_table	*parser(char **lex)
{
	t_cmd_table	*cmd_table;

	cmd_table = init_table(lex);
	init_tab(lex, cmd_table);
	init_cmd(lex, cmd_table);
	return (cmd_table);
}
