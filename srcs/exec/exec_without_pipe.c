/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_without_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:25:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 22:43:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_without_pipe(t_cmd_table *cmd_table, t_env_list **env, int cnt)
{
	int	pid;

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

void	do_exec_without_pipe(t_cmd_table *cmd_table, t_env_list **env)
{
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
		exec_builtin(cmd_table, env, NULL, cmd_table);
		return ;
	}
	fork_without_pipe(cmd_table, env, cnt);
}
