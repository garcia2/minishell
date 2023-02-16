/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:01:20 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/16 18:12:52 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env_len(char *str, int *i, int *len)
{
	char	*env;

	env = get_env(str, i);
	if (env == NULL)
		return (0);
	(*len) += ft_strlen(env);
	free(env);
	return (1);
}

static int	get_new_len(char *str)
{
	int		i;
	int		len;
	int		is_in_quotes;

	is_in_quotes = 0;
	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			is_in_quotes = !is_in_quotes;
		if (str[i] == '$' && !is_in_quotes)
		{
			if (add_env_len(str, &i, &len) == 0)
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

static int	copy_env(char	*new_str, char	*str, int *new_i, int *i)
{
	char	*env;

	env = get_env(str, i);
	if (env == NULL)
		return (0);
	ft_strlcpy(new_str + *new_i, env, ft_strlen(env) + 1);
	(*new_i) += ft_strlen(env);
	return (1);
}

static int	copy_and_replace(char	*new_str, char	*str)
{
	int		i;
	int		new_i;
	int		is_in_quotes;

	is_in_quotes = 0;
	i = 0;
	new_i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			is_in_quotes = !is_in_quotes;
		if (str[i] == '$' && !is_in_quotes)
		{
			if (copy_env(new_str, str, &new_i, &i) == 0)
				return (0);
		}
		else
		{
			new_str[new_i] = str[i];
			i++;
			new_i++;
		}
	}
	return (1);
}

char	*replace_env_var(char *str)
{
	char	*new_str;
	int		new_len;

	new_len = get_new_len(str);
	printf("len = %d\n", new_len);
	new_str = ft_calloc(sizeof(char), new_len + 1);
	if (new_str == NULL)
		return (NULL);
	if (copy_and_replace(new_str, str) == 0)
		return (free(new_str), NULL);
	printf("new_str =%s\n", new_str);
	return (new_str);
}
