/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:00:04 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/31 13:20:52 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env;

	if (argc != 1)
		return (printf("NO ARGS REQUIRED\n"), 1);
	(void) argv;
	env = parse_env(envp);
	if (env == NULL)
		return (2);
	launcher();
	env_lst_clear(&env);
	return (0);
}
