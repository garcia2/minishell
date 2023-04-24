/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:04:25 by jileroux          #+#    #+#             */
/*   Updated: 2023/04/22 18:27:51 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
	{
		printf("Error cannot get repository\n");
		return (2);
	}
	printf("%s\n", path);
	return (0);
}
