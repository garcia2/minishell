/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:01:20 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 12:31:14 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env_len(char *str, int *i, int *len, t_env_list *env)
{
	char	*env_var;

	env_var = get_env(str, i, env);
	if (env_var == NULL)
		return (0);
	(*len) += ft_strlen(env_var);
	free(env_var);
	return (1);
}

static int	get_new_len(char *str, t_env_list *env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !is_white_space(str[i + 1]) && str[i + 1] != '\0')
		{
			if (add_env_len(str, &i, &len, env) == 0)
				return (-1);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static int	copy_env(char	*new_str, char	**str, int *new_i, t_env_list *env)
{
	char	*env_var;
	int		i;

	i = 0;
	env_var = get_env(*str, &i, env);
	*str += i;
	if (env_var == NULL)
		return (0);
	ft_strlcpy(new_str + *new_i, env_var, ft_strlen(env_var) + 1);
	(*new_i) += ft_strlen(env_var);
	free(env_var);
	return (1);
}

static int	copy_and_replace(char	*new_str, char	*str, t_env_list *env)
{
	int		new_i;
	int		is_in_quotes;

	is_in_quotes = 0;
	new_i = 0;
	while (*str != '\0')
	{
		if (*str == '\'')
			is_in_quotes = !is_in_quotes;
		if (*str == '$' && !is_white_space(*(str + 1)) && *(str + 1) != '\0')
		{
			if (copy_env(new_str, &str, &new_i, env) == 0)
				return (0);
		}
		else
		{
			new_str[new_i] = *str;
			str++;
			new_i++;
		}
	}
	return (1);
}

char	*replace_env_var(char *str, t_env_list *env)
{
	char	*new_str;
	int		new_len;

	new_len = get_new_len(str, env);
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	if (copy_and_replace(new_str, str, env) == 0)
		return (free(new_str), NULL);
	return (new_str);
}
