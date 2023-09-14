/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:26:25 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 23:05:26 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_num_arg_error(char *arg)
{
	print_error("minishell : exit: ");
	print_error(arg);
	print_error(": numeric argument required\n");
}

void	mini_exit(t_cmd_table *cmd_table, t_env_list **env,
t_pipex *pipex, t_cmd_table *cmd_table_save)
{
	if (pipex != NULL)
		free_pipex(pipex);
	else
		write (1, "exit\n", 5);
	if (cmd_table->cmd[1] == NULL)
		g_error = 0;
	else
	{
		if (!is_str_digit(cmd_table->cmd[1]))
		{
			print_num_arg_error(cmd_table->cmd[1]);
			g_error = 2;
		}
		else if (cmd_table->cmd[2] != NULL)
		{
			g_error = 1;
			print_error("minishell : exit: too many arguments\n");
			return ;
		}
		else
			g_error = ft_atoi(cmd_table->cmd[1]);
	}
	env_lst_clear(env);
	clear_lst(&cmd_table_save);
	exit (g_error);
}
