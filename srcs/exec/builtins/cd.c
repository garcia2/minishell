/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:11:56 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 13:19:44 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_oldpwd(t_env_list *env)
{
	char		path[1024];
	t_env_list	*env_tmp;

	env_tmp = env;
	while (env && ft_strcmp(env->key, "OLDPWD"))
		env = env->next;
	while (env_tmp && ft_strcmp(env_tmp->key, "PWD"))
		env_tmp = env_tmp->next;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(env_tmp->value);
	if (env_tmp->value)
		free(env_tmp->value);
	getcwd(path, 1024);
	env_tmp->value = ft_strdup(path);
	return (0);
}

int	change_directory(char *cmd, t_env_list *env)
{
	char	*path;

	(void)env;
	path = cmd;
	if (chdir(path) == -1)
	{
		if (access(path, F_OK) == 0)
		{
			printf("Minishell: cd: Not a directory\n");
			g_error = 1;
		}
		else
		{
			printf("Minishell: cd: No such file or directory\n");
			g_error = 1;
		}
		return (2);
	}
	change_oldpwd(env);
	return (0);
}
