/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:31:53 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 20:45:58 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table	*init_table(char **lex, t_env_list *env)
{
	int			i;
	t_cmd_table	*cmd_table;
	t_cmd_table	*tmp;

	if (lex[0] == NULL)
		return (init_node());
	i = 0;
	cmd_table = NULL;
	while (lex[i])
	{
		tmp = init_node();
		if (tmp == NULL)
			return (NULL);
		init_redir(lex, tmp, &i, env);
		init_signal();
		if (lex[i])
			i++;
		add_back(&cmd_table, tmp);
	}
	return (cmd_table);
}

t_cmd_table	*parser(char **lex, t_env_list *env)
{
	t_cmd_table	*cmd_table;

	cmd_table = init_table(lex, env);
	init_tab(lex, cmd_table);
	if (init_cmd(lex, cmd_table) == 0)
		return (clear_lst(&cmd_table), NULL);
	f_expand_command_table(cmd_table, env);
	return (cmd_table);
}
