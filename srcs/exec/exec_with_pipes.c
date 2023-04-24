/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:34:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/24 16:24:24 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_cmd_table *cmd_table)
{
	int	nb_pipe;

	nb_pipe = 0;
	while (cmd_table != NULL)
	{
		nb_pipe++;
		cmd_table = cmd_table->next;
	}
	return (nb_pipe);
}

int	exec_pipex_command(t_pipex *pipex, int pid, t_cmd_table *cmd_table, t_env_list *env)
{
	if (ft_dup(pipex, pid) == 0)
	{
		free_pipex(pipex);
		exit(1);
	}
	if (cmd_table->infile_fd < 0 || cmd_table->outfile_fd < 0)
	{
		print_error("ERROR: PROBLEM WITH DUP_FILES\n");
		exit(1);
	}
	if (cmd_table->cmd == NULL || cmd_table->cmd[0] == NULL)
		exit(1);
	if (is_builtin(cmd_table->cmd[0]))
	{
		exec_builtin(cmd_table, env);
		clear_lst(&cmd_table);
		env_lst_clear(&env);
		close_all_pipes(pipex);
		free_pipex(pipex);
		exit(1);
	}
	if (dup_files(cmd_table) == 0)
	{
		print_error("ERROR: PROBLEM WITH DUP_FILES\n");
		clear_lst(&cmd_table);
		env_lst_clear(&env);
		exit(2);
	}
	simple_exec(cmd_table, env);
	return (1);
}

void	do_exec_with_pipes(t_cmd_table *cmd_table, t_env_list *env)
{
	t_pipex	*pipex;

	pipex = get_pipex(count_pipe(cmd_table));
	if (pipex == NULL)
		return ;
	pipex_process(pipex, cmd_table, env);
	free_pipex(pipex);
}
