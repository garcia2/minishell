/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:02:58 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/31 14:43:59 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_cmd_table *cmd_table)
{
	int	i;

	printf("\n PARSER \n\n");
	while (cmd_table)
	{
		i = 0;
		printf("infile : %d\n", cmd_table->infile_fd);
		printf("outfile : %d\n", cmd_table->outfile_fd);
		while (cmd_table->cmd && cmd_table->cmd[i])
		{
			printf("cmd : %s\n", cmd_table->cmd[i]);
			i++;
		}
		printf("\nnext cmd ->\n\n");
		cmd_table = cmd_table->next;
	}
}

void	delete_file(void)
{
	int		i;
	char	*temp_file_name;
	char	*itoa_i;

	i = 1;
	itoa_i = ft_itoa(i);
	temp_file_name = ft_strjoin(".temp_file_tmp", itoa_i);
	while (access(temp_file_name, R_OK) == 0)
	{
		unlink(temp_file_name);
		free(itoa_i);
		free(temp_file_name);
		i++;
		itoa_i = ft_itoa(i);
		temp_file_name = ft_strjoin(".temp_file_tmp", itoa_i);
	}
	free(itoa_i);
	free(temp_file_name);
}

int	launcher(t_env_list *env)
{
	if (env == NULL)
		return (2);
	init_signal();
	while (1)
	{
		if (minishell(env) == 2)
			return (1);
	}
	rl_clear_history();
	dprintf(STDOUT_FILENO, "exit\n");
	return (0);
}

int	minishell(t_env_list *env)
{
	t_cmd_table	*cmd_table;
	char		*command;
	char		**lex;

	command = readline(">> ");
	if (command == NULL || ft_strcmp(command, "exit") == 0)
		return (2);
	add_history(command);
	lex = lexer(command);
	free(command);
	if (lex == NULL)
		return (2);
	print_lexer(lex);
	cmd_table = parser(lex, env);
	if (cmd_table == NULL)
		return (free_lexer(lex), 2);
	print_list(cmd_table);
	do_exec(cmd_table);
	free_lexer(lex);
	clear_lst(&cmd_table);
	delete_file();
	return (0);
}
