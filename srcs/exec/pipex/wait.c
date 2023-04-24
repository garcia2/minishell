/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:20:25 by nico              #+#    #+#             */
/*   Updated: 2023/04/24 13:13:32 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	waitforit(t_pipex *pipex)
{
	int	i;
	int	error_code;
	int	status;

	i = 0;
	error_code = 0;
	while (i < pipex->nb_cmd)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
			error_code = WEXITSTATUS(status);
		i++;
	}
	return (error_code);
}
