/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:31:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/21 17:22:27 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static t_env_list	*split_env(char *envp_line)
{
	int			equal_id;
	t_env_list	*new_env;

	equal_id = find_char(envp_line, '=');
	if (equal_id == -1)
		return (NULL);
	envp_line[equal_id] = '\0';
	new_env = env_lstnew(envp_line, envp_line + equal_id + 1);
	return (new_env);
}

int	increment_shlvl(t_env_list *env)
{
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = get_env_by_key(env, "SHLVL");
	if (shlvl_str == NULL)
		return (0);
	printf("shlvl = %s\n", shlvl_str);
	shlvl_int = ft_atoi(shlvl_str);
	printf("shlvl_int = %d\n", shlvl_int);
	free(shlvl_str);
	shlvl_str = ft_itoa(shlvl_int + 1);
	if (shlvl_str == NULL)
		return (0);
	printf("new_shlvl = %s\n", shlvl_str);
	return (set_env_by_key(env, "SHLVL", shlvl_str));
}

t_env_list	*parse_env(char **envp)
{
	t_env_list	*env_lst;
	t_env_list	*cur;
	int			i;

	env_lst = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		cur = split_env(envp[i]);
		if (cur == NULL)
			return (env_lst_clear(&env_lst), NULL);
		env_lst_add_back(&env_lst, cur);
		i++;
	}
	if (increment_shlvl(env_lst) == 0)
		return (env_lst_clear(&env_lst), NULL);
	return (env_lst);
}
