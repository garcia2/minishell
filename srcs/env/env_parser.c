/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:31:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/14 20:26:26 by nigarcia         ###   ########.fr       */
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
	shlvl_int = ft_atoi(shlvl_str);
	free(shlvl_str);
	shlvl_str = ft_itoa(shlvl_int + 1);
	if (shlvl_str == NULL)
		return (0);
	return (set_env_by_key(env, "SHLVL", shlvl_str));
}

t_env_list	*basic_env(void)
{
	t_env_list	*env;

	env = env_lstnew(ft_strdup("PATH"), ft_strdup("/bin"));
	env_lst_add_back(&env, env_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
	return (env);
}

t_env_list	*parse_env(char **envp)
{
	t_env_list	*env_lst;
	t_env_list	*cur;
	int			i;

	env_lst = NULL;
	i = 0;
	if (envp[0] == NULL)
		return (basic_env());
	while (envp[i] != NULL)
	{
		cur = split_env(envp[i]);
		if (cur == NULL)
			return (env_lst_clear(&env_lst), NULL);
		env_lst_add_back(&env_lst, cur);
		i++;
	}
	return (env_lst);
}
