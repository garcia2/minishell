/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:39:24 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/07 13:31:15 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signal(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, &handler_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(int sig)
{
	(void)sig;
	g_error = 42;
	close(STDIN_FILENO);
	return ;
}
