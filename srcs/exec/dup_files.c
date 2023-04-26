/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:30:36 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/26 16:05:42 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_files(t_cmd_table *cmd_table)
{
	if (cmd_table->infile_fd > 2)
	{
		dup2(cmd_table->infile_fd, 0);
		close(cmd_table->infile_fd);
	}
	if (cmd_table->outfile_fd > 2)
	{
		dup2(cmd_table->outfile_fd, 1);
		close(cmd_table->outfile_fd);
	}
	return (1);
}
