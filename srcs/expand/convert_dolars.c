/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dolars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:52:16 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 16:56:26 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	convert_dolars_process(char **lex, int i, t_env_list *env)
{
	char	*temp_str;

	if (lex[i][0] == '\"')
	{
		temp_str = replace_env_var(lex[i], env);
		if (temp_str == NULL)
			return (0);
		free(lex[i]);
		lex[i] = temp_str;
	}
	else if (lex[i][0] != '\'')
	{
		temp_str = replace_env_var(lex[i], env);
		if (temp_str == NULL)
			return (0);
		free(lex[i]);
		lex[i] = temp_str;
	}
	return (1);
}

int	convert_dolars(char **lex, t_env_list *env)
{
	int		i;

	i = 0;
	while (lex[i] != NULL)
	{
		if (convert_dolars_process(lex, i, env) == 0)
			return (0);
		i++;
	}
	return (1);
}
