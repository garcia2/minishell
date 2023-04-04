/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:09 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/04 15:07:14 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_table *cmd_table, t_env_list *env)
{
	if (ft_strcmp(cmd_table->cmd[0], "cd") == 0
		|| ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
		pwd_cd(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "export") == 0)
		export(env, cmd_table->cmd);
	else if (ft_strcmp(cmd_table->cmd[0], "unset") == 0)
		unset(env, cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "env") == 0)
		export(env, NULL);
	return (1);
}

void	simple_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	if (set_command_path(cmd_table, env) == 0)
	{
		printf("PROBLEM WITH SET_COMMAND_PATH\n");
		exit(1);
	}
	if (execve(cmd_table->cmd[0], cmd_table->cmd, NULL) == -1)
	{
		printf("PROBLEM WITH EXECVE\n");
		exit(1);
	}
}

void	do_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	int	pid;
	int	i;

	printf("\nEXECUTION\n");
	if (is_builtin(cmd_table->cmd[0]))
	{
		exec_builtin(cmd_table, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup_files(cmd_table);
		if (ft_strcmp(cmd_table->cmd[0], "echo") == 0)
		{
			i = 0;
			do_echo(cmd_table, &i);
			exit(0);
		}
		else
		{
			simple_exec(cmd_table, env);
		}	
	}
	else
		waitpid(pid, NULL, 0);
}
