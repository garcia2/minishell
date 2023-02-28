/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:23 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/28 17:00:28 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_check_args(char	*args)
{
	int	i;

	if ((ft_strlen(args) == 0) || ft_isdigit(args[0]))
		return (0);
	i = 0;
	while (args[i] != '\0' && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_print(t_env_list *env)
{
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("export %s=\"%s\"\n", env->key, env->value);
		else
			printf("export %s\n", env->key);
		env = env->next;
	}
}

int	export_parse_args(char *args, char **key, char **value)
{
	int			equal_id;

	*key = NULL;
	*value = NULL;
	equal_id = find_char(args, '=');
	if (equal_id < 0)
	{
		return (1);
	}
	else
	{
		*key = ft_calloc(equal_id + 1, sizeof(char));
		if (*key == NULL)
			return (0);
		*value = ft_calloc(ft_strlen(args) - equal_id, sizeof(char));
		if (*value == NULL)
			return (free(*key), 0);
		ft_strlcpy(*key, args, equal_id + 1);
		ft_strlcpy(*value, args + equal_id + 1, ft_strlen(args) - equal_id);
		return (1);
	}
}

static int	export_add_var(t_env_list *env, char *args)
{
	t_env_list	*new_env_var;
	char		*key;
	char		*value;

	export_parse_args(args, &key, &value);
	new_env_var = env_lstnew(key, value);
	free(key);
	free(value);
	if (new_env_var == NULL)
		return (0);
	env_lst_add_back(&env, new_env_var);
	return (1);
}

int	export(t_env_list *env, char *args)
{
	if (args == NULL)
		export_print(env);
	else
	{
		if (!export_check_args(args))
			return (printf("Export : invalid args\n"), 0);
		if (export_add_var(env, args) == 0)
			return (printf("Problem with export\n"), 0);
	}
	return (1);
}
