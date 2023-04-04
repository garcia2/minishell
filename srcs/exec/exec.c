/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:09 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/04 14:50:42 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_table *cmd_table, t_env_list *env)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd_table->cmd[i], "echo") == 0)
		do_echo(cmd_table, &i);
	else if (ft_strcmp(cmd_table->cmd[i], "pwd") == 0)
		pwd_cd(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[i], "export") == 0)
		export(env, cmd_table->cmd);
	else if (ft_strcmp(cmd_table->cmd[i], "unset") == 0)
		unset(env, cmd_table);
	else if (ft_strcmp(cmd_table->cmd[i], "env") == 0)
		export(env, NULL);
	return (1);
}

void	simple_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	if (set_command_path(cmd_table, env) == 0)
	{
		printf("PROBLEM WITH SET_COMMAND_PATH\n");
		return ;
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

	if (ft_strcmp(cmd_table->cmd[0], "cd") == 0)
	{
		pwd_cd(cmd_table);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		printf("\nEXECUTION\n");
		dup_files(cmd_table);
		if (is_builtin(cmd_table->cmd[0]))
		{
			exec_builtin(cmd_table, env);
			exit (0);
		}
		else
		{
			simple_exec(cmd_table, env);
		}	
	}
	else
		waitpid(pid, NULL, 0);
}
