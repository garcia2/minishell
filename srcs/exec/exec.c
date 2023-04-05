/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:09 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/05 16:40:23 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_table *cmd_table, t_env_list *env)
{
	if (ft_strcmp(cmd_table->cmd[0], "echo") == 0)
		do_echo(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "cd") == 0
		|| ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
		pwd_cd(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "export") == 0)
		export(env, cmd_table->cmd + 1);
	else if (ft_strcmp(cmd_table->cmd[0], "unset") == 0)
		unset(env, cmd_table->cmd + 1);
	else if (ft_strcmp(cmd_table->cmd[0], "env") == 0)
		env_lst_print(env);
	return (1);
}

void	simple_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	if (set_command_path(cmd_table, env) == 0)
	{
		print_command_not_found_error(cmd_table->cmd[0]);
		clear_lst(&cmd_table);
		env_lst_clear(&env);
		exit(1);
	}
	if (execve(cmd_table->cmd[0], cmd_table->cmd, NULL) == -1)
	{
		printf("PROBLEM WITH EXECVE\n");
		clear_lst(&cmd_table);
		env_lst_clear(&env);
		exit(1);
	}
}

void	do_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	int	pid;

	if (cmd_table->cmd == NULL)
		return ;
	if (is_builtin(cmd_table->cmd[0]))
	{
		exec_builtin(cmd_table, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup_files(cmd_table);
		simple_exec(cmd_table, env);
	}
	else
		waitpid(pid, NULL, 0);
}
