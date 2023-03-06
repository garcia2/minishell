/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:24:51 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/06 13:35:11 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_instruction(t_cmd_table *command_table)
{
	int	nb_instruction;

	nb_instruction = 0;
	while (command_table != NULL)
	{
		nb_instruction++;
		command_table = command_table->next;
	}
	return (nb_instruction);
}

int	execute_instructions(t_cmd_table *command_table, t_env_list *env)
{
	int	nb_instruction;

	(void) env;
	nb_instruction = get_nb_instruction(command_table);
	if (nb_instruction == 1)
		return (simple_exec(command_table, env));
	printf("nb_instruction: %d\n", nb_instruction);
	return (1);
}
