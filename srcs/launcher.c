/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:02:58 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/12 17:17:33 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char *command)
{
	if (command == NULL)
	{
		write (1, "exit\n", 5);
		return (2);
	}
	if (ft_strcmp(command, "exit") == 0)
	{
		write (1, "exit\n", 5);
		return (2);
	}
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
	init_signal();
	while (1)
	{
		g_error = 0;
		if (minishell(env) == 2)
			return (1);
	}
	rl_clear_history();
	dprintf(STDOUT_FILENO, "exit\n");
	return (0);
}

// int	minishell(t_env_list *env)
// {
// 	t_cmd_table	*cmd_table;
// 	char		*command;
// 	char		**lex;

// 	command = readline(">> ");
// 	if (check_cmd(command) == 2)
// 		return (2);
// 	else if (check_cmd(command) == 1)
// 		return (1);
// 	lex = lexer(command);
// 	free(command);
// 	if (lex == NULL)
// 		return (2);
// 	cmd_table = parser(lex, env);
// 	free_lexer(lex);
// 	if (cmd_table == NULL)
// 		return (2);
// 	if (g_error != 42)
// 		do_exec(cmd_table, env);
// 	clear_lst(&cmd_table);
// 	delete_file();
// 	return (0);
// }

int	minishell(t_env_list *env)
{
	t_cmd_table	*cmd_table;
	char		*command;
	char		**lex;
	char		**tab;

	command = readline(">> ");
	if (check_cmd(command) == 2)
		return (2);
	else if (check_cmd(command) == 1)
		return (1);
	// extract_dollars(command, env);	
	// extract_quotes(command);
	// printf("[%s] => [%s]\n", command, replace_env_var(command, env));
	//tab = expand_process(command, env);
	//print_lexer(tab);
	//free_lexer(tab);
	///split_spaces_witout_quotes(command);
	lex = lexer(command);
	free(command);
	if (lex == NULL)
		return (2);
	cmd_table = parser(lex, env);
	free_lexer(lex);
	if (cmd_table == NULL)
		return (2);
	tab = expands(cmd_table->cmd, env);
	free_lexer(cmd_table->cmd);
	cmd_table->cmd = tab;
	print_command_table(cmd_table);
	if (g_error != 42)
		do_exec(cmd_table, env);
	clear_lst(&cmd_table);
	delete_file();
	return (0);
}