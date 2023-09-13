/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:09 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/13 16:05:01 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_table *cmd_table, t_env_list *env)
{
	if (ft_strcmp(cmd_table->cmd[0], "echo") == 0)
		do_echo(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "cd") == 0
		|| ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
		pwd_cd(cmd_table, env);
	else if (ft_strcmp(cmd_table->cmd[0], "export") == 0)
		export(env, cmd_table->cmd + 1);
	else if (ft_strcmp(cmd_table->cmd[0], "unset") == 0)
	{
		unset(env, cmd_table->cmd + 1);
		printf("PRINT OF ENV\n\n\n\n\n");
		env_lst_print(env);
		
	}
	else if (ft_strcmp(cmd_table->cmd[0], "env") == 0)
		env_lst_print(env);
	else if (ft_strcmp(cmd_table->cmd[0], "exit") == 0)
	{
		env_lst_clear(&env);
		clear_lst(&cmd_table);
		write (1, "exit\n", 5);
		exit (g_error);
	}
	return (1);
}

void	simple_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	char		**env_tab;
	t_cmd_table	*tmp;

	tmp = cmd_table;
	if (set_command_path(cmd_table, env) == 0)
	{
		print_command_not_found_error(cmd_table->cmd[0]);
		crit_exit(cmd_table, env, NULL, 1);
	}
	env_tab = get_env_tab(env);
	if (env_tab == NULL)
	{
		print_error("PROBLEM WITH GET_ENV_TAB");
		crit_exit(cmd_table, env, NULL, 1);
	}
	while (tmp)
	{
		check_fd_closed(tmp->outfile_fd);
		tmp = tmp->next;
	}
	if (execve(cmd_table->cmd[0], cmd_table->cmd, env_tab) == -1)
	{
		print_command_not_found_error(cmd_table->cmd[0]);
		crit_exit(cmd_table, env, NULL, 1);
	}
}

void	do_exec_without_pipe(t_cmd_table *cmd_table, t_env_list *env)
{
	int	pid;
	int	cnt;

	cnt = 0;
	if (cmd_table->infile_fd < 0 || cmd_table->outfile_fd < 0)
	{
		print_error("ERROR: PROBLEM WITH DUP_FILES\n");
		perror(NULL);
		return ;
	}
	if (cmd_table->cmd == NULL || cmd_table->cmd[0] == NULL)
		return ;
	if (is_builtin(cmd_table->cmd[0]))
	{
		exec_builtin(cmd_table, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (dup_files(cmd_table) == 0)
		{
			print_error("ERROR: PROBLEM WITH DUP_FILES\n");
			perror(NULL);
			crit_exit(cmd_table, env, NULL, 1);
		}
		init_signal2();
		simple_exec(cmd_table, env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		child_exit(pid, &cnt);
		init_signal();
	}
}

void	do_exec(t_cmd_table *cmd_table, t_env_list *env)
{
	if (cmd_table->next == NULL)
		do_exec_without_pipe(cmd_table, env);
	else
		do_exec_with_pipes(cmd_table, env);
}
