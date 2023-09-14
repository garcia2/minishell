/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:34:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 23:49:33 by nigarcia         ###   ########.fr       */
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

int	exec_ppx_cmd(t_pipex *pipex, t_cmd_table *cmd_tab,
t_env_list **env, t_cmd_table *cmd_table_save)
{
	if (ft_dup(pipex, pipex->pid) == 0)
		crit_exit(cmd_table_save, env, pipex, 1);
	if (cmd_tab->infile_fd < 0 || cmd_tab->outfile_fd < 0)
	{
		perror("minishell");
		g_error = 1;
		crit_exit(cmd_table_save, env, pipex, 1);
	}
	if (cmd_tab->cmd == NULL || cmd_tab->cmd[0] == NULL)
		crit_exit(cmd_table_save, env, pipex, 1);
	if (is_builtin(cmd_tab->cmd[0]))
	{
		exec_builtin(cmd_tab, env, pipex, cmd_table_save);
		crit_exit(cmd_table_save, env, pipex, 0);
	}
	if (dup_files(cmd_tab) == 0)
		crit_exit(cmd_table_save, env, pipex, 1);
	simple_exec(cmd_tab, env, pipex, cmd_table_save);
	return (1);
}

void	do_exec_with_pipes(t_cmd_table *cmd_table, t_env_list **env)
{
	t_pipex	*pipex;

	pipex = get_pipex(count_pipe(cmd_table));
	if (pipex == NULL)
		return ;
	g_error = pipex_process(pipex, cmd_table, env);
	free_pipex(pipex);
}
