/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:00:04 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 17:10:05 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shlvl_increment(t_env_list *env)
{
	int	value;

	while (env && ft_strcmp(env->key, "SHLVL"))
		env = env->next;
	value = ft_atoi(env->value);
	free(env->value);
	value++;
	env->value = ft_itoa(value);
	return (0);
}

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
	shlvl_increment(env);
	launcher(&env);
	env_lst_clear(&env);
	return (0);
}
