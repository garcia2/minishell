/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:17:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/12 18:31:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_token(char *str, int *i)
{
	int len;

	len = 0;
	while (!is_white_space(str[*i])
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '\0')
	{
		(*i)++;
		len++;
	}
	return (len);
}

char *get_env(char *str, int *i)
{
	int 	begin;
	int 	len;
	char	*var_name;
	char	*var;

	begin = *i;
	len = skip_token(str, i);
	if (len == 0)
		return (NULL);
	var_name = ft_calloc(sizeof(char), len + 1);
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, str + begin, len + 1);
	var = getenv(var_name);
	printf("var_name = %s\n", var_name);
	printf("var = %s\n", var);
	return (free(var_name), var);
}
