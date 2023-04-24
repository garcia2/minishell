/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:02:58 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/07 14:50:51 by jileroux         ###   ########.fr       */
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

int	check_cmd(char *command)
{
	if (command == NULL || ft_strcmp(command, "exit") == 0)
		return (2);
	if (strcmp(command, "\0") == 0)
		return (1);
	add_history(command);
	return (0);
}

int	delete_file(void)
{
	int		i;
	char	*temp_file_name;
	char	*itoa_i;

	i = 1;
	itoa_i = ft_itoa(i);
	temp_file_name = ft_strjoin(".temp_file_tmp", itoa_i);
	if (temp_file_name == NULL)
		return (write(1, "Error : can't create file\n", 27), 0);
	while (access(temp_file_name, R_OK) == 0)
	{
		unlink(temp_file_name);
		free(itoa_i);
		free(temp_file_name);
		i++;
		itoa_i = ft_itoa(i);
		temp_file_name = ft_strjoin(".temp_file_tmp", itoa_i);
		if (temp_file_name == NULL)
			return (write(1, "Error : can't create file\n", 27), 0);
	}
	free(itoa_i);
	free(temp_file_name);
	return (1);
}

int	launcher(t_env_list *env)
{
	if (env == NULL)
		return (2);
	while (1)
	{
		g_error = 0;
		init_signal();
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

	add_history("cat << eof > f1");
	command = readline(">> ");
	if (check_cmd(command) == 2)
		return (2);
	else if (check_cmd(command) == 1)
		return (1);
	lex = lexer(command);
	free(command);
	if (lex == NULL)
		return (2);
	print_lexer(lex);
	cmd_table = parser(lex, env);
	if (cmd_table == NULL)
		return (free_lexer(lex), 2);
	print_list(cmd_table);
	if (g_error != 42)
		do_exec(cmd_table, env);
	free_lexer(lex);
	clear_lst(&cmd_table);
	delete_file();
	return (0);
}
