/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:42:02 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 21:22:02 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_command_not_found_error(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": command not found\n");
}

void	print_no_such_file(char *cmd)
{
	print_error("minishell: ");
	print_error(cmd);
	print_error(": No such file or directory\n");
}

void	crit_exit(t_cmd_table *cmd_tab,
t_env_list **env, t_pipex *pipex, int ec)
{
	if (cmd_tab != NULL)
		clear_lst(&cmd_tab);
	if (env != NULL)
		env_lst_clear(env);
	if (pipex != NULL)
	{
		close_all_pipes(pipex);
		close_pipex_dup(pipex);
		free_pipex(pipex);
	}
	delete_file();
	exit(ec);
}
