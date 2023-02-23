/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:01:20 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/23 15:57:19 by nigarcia         ###   ########.fr       */
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
	free(env);
	return (1);
}

static int is_heredoc_limiter(char *str, int i)
{
	while (i > 0 && !is_white_space(str[i]))
		i--;
	while (i > 0 && is_white_space(str[i]))
		i--;
	printf("i = %d, i - 1 = %d\n", i, i - 1);
	if (i < 1)
		return (0);
	if (str[i] == '<' && str[i - 1] == '<')
		return (1);
	else
		return (0);
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
		if (str[i] == '$' && !is_in_quotes && !is_heredoc_limiter(str, i))
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
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	if (copy_and_replace(new_str, str) == 0)
		return (free(new_str), NULL);
	return (new_str);
}
