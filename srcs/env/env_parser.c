/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:31:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/29 16:54:03 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_char(char *str, char c)
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
	envp_line[equal_id] = '\0';
	new_env = env_lstnew(envp_line, envp_line + equal_id +1);
	return (new_env);
}

char	*get_env_by_key(t_env_list *env_lst, char *key)
{
	while (env_lst != NULL)
	{
		if (strcmp(env_lst->key, key) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
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
	return (env_lst);
}
