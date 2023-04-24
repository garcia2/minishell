/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:00:04 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/22 14:22:34 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env;

	if (argc != 1)
		return (print_error("ERROR: NO ARGS REQUIRED\n"), 1);
	(void) argv;
	env = parse_env(envp);
	if (env == NULL)
		return (print_error("ERROR: PROBLEM WITH ENV PARSING\n"), 2);
	launcher(env);
	env_lst_clear(&env);
	return (0);
}
