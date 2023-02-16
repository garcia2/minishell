/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:17:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/16 17:51:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_token_with_dolar(char *str, int *i)
{
	int	len;

	len = 0;
	while (!is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '$'
		&& str[*i] != '\0')
	{
		(*i)++;
		len++;
	}
	return (len);
}

char	*get_env(char *str, int *i)
{
	int		begin;
	int		len;
	char	*var_name;
	char	*var;

	(*i)++;
	begin = *i;
	len = skip_token_with_dolar(str, i);
	if (len == 0)
		return (ft_strdup(""));
	var_name = ft_calloc(sizeof(char), len + 1);
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, str + begin, len + 1);
	var = getenv(var_name);
	printf("var_name = %s\n", var_name);
	printf("var = %s\n", var);
	if (var == NULL)
		return (free(var_name), ft_strdup(""));
	else
		return (free(var_name), ft_strdup(var));
}
