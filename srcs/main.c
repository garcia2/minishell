/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:00:04 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/15 00:19:13 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shlvl_increment(t_env_list *env)
{
	int	value;

	while (env && ft_strcmp(env->key, "SHLVL"))
		env = env->next;
	if (env == NULL)
		return (1);
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
		return (1);
	(void) argv;
	env = parse_env(envp);
	if (env == NULL)
		return (2);
	shlvl_increment(env);
	launcher(&env);
	env_lst_clear(&env);
	return (0);
}
