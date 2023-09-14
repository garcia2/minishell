/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:51:32 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 11:07:04 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_error(int *cnt)
{
	if (g_error == 128 + SIGTERM)
		ft_putstr_fd("Terminated\n", STDERR_FILENO);
	else if (g_error == 128 + SIGSEGV)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	else if (g_error == 128 + SIGQUIT && !(*cnt))
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		(*cnt)++;
	}
	else if (g_error == 128 + SIGABRT)
		ft_putstr_fd("Aborted (core dumped)\n", STDERR_FILENO);
}

void	child_exit(int pid, int *cnt)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_error = 128 + WTERMSIG(status);
		signal_error(cnt);
	}
}
