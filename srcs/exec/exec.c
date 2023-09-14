/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:09 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/15 00:03:05 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd_table *cmd_table, t_env_list **env,
t_pipex *pipex, t_cmd_table *cmd_table_save)
{
	if (ft_strcmp(cmd_table->cmd[0], "echo") == 0)
		do_echo(cmd_table);
	else if (ft_strcmp(cmd_table->cmd[0], "cd") == 0
		|| ft_strcmp(cmd_table->cmd[0], "pwd") == 0)
		pwd_cd(cmd_table, *env);
	else if (ft_strcmp(cmd_table->cmd[0], "export") == 0)
		export(env, cmd_table->cmd + 1);
	else if (ft_strcmp(cmd_table->cmd[0], "unset") == 0)
		unset(env, cmd_table->cmd + 1);
	else if (ft_strcmp(cmd_table->cmd[0], "env") == 0)
		env_lst_print(*env);
	else if (ft_strcmp(cmd_table->cmd[0], "exit") == 0)
		mini_exit(cmd_table, env, pipex, cmd_table_save);
	return (1);
}

void	check_command_path(t_cmd_table *cmd_table, t_env_list **env,
	t_pipex *pipex, t_cmd_table *save)
{
	int	error;

	error = set_command_path(cmd_table, *env);
	if (error == 0)
	{
		print_command_not_found_error(cmd_table->cmd[0]);
		crit_exit(save, env, pipex, 127);
	}
	else if (error == -1)
	{
		print_no_such_file(cmd_table->cmd[0]);
		crit_exit(save, env, pipex, 127);
	}
}

void	simple_exec(t_cmd_table *cmd_table, t_env_list **env,
t_pipex *pipex, t_cmd_table *save)
{
	char		**env_tab;
	t_cmd_table	*tmp;

	tmp = cmd_table;
	check_command_path(cmd_table, env, pipex, save);
	env_tab = get_env_tab(*env);
	if (env_tab == NULL)
		crit_exit(save, env, NULL, 1);
	while (tmp)
	{
		check_fd_closed(tmp->outfile_fd);
		tmp = tmp->next;
	}
	exec_check_fd_close();
	if (execve(cmd_table->cmd[0], cmd_table->cmd, env_tab) == -1)
	{
		free_lexer(env_tab);
		print_command_not_found_error(cmd_table->cmd[0]);
		crit_exit(save, env, pipex, 127);
	}		
}

void	do_exec(t_cmd_table *cmd_table, t_env_list **env)
{
	if (cmd_table->next == NULL)
		do_exec_without_pipe(cmd_table, env);
	else
		do_exec_with_pipes(cmd_table, env);
}
