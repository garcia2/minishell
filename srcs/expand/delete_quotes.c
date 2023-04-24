/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:01:13 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/24 12:25:02 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quotes_process(char *str)
{
	char	*new_str;

	if (str[0] == '\'' || str[0] == '"')
	{
		new_str = ft_calloc(ft_strlen(str) - 1, sizeof(char));
		if (new_str == NULL)
			return (NULL);
		ft_strlcpy(new_str, str + 1, ft_strlen(str) - 1);
		return (new_str);
	}
	else
		return (ft_strdup(str));
}

int	delete_quotes(char **split)
{
	int		i;
	char	*deleted_quotes_str;

	i = 0;
	while (split[i] != NULL)
	{
		deleted_quotes_str = delete_quotes_process(split[i]);
		if (deleted_quotes_str == NULL)
			return (0);
		free(split[i]);
		split[i] = deleted_quotes_str;
		i++;
	}
	return (1);
}
