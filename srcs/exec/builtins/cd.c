/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:11:56 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/17 13:56:17 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(char *cmd)
{
	char	*path;

	path = cmd;
	printf("path : %s\n", path);
	if (chdir(path) == -1)
	{
		printf("Minishell: cd: No such file or directory\n");
		return (2);
	}
	return (0);
}
