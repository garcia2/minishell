/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:46:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/29 12:12:07 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_str_nb_part(char *str)
{
	int		nb_part;
	int		i;

	nb_part = 0;
	i = 0;
	while (str[i] != '\0')
	{	
		nb_part++;
		if (is_quote(str[i]))
		{
			i++;
			go_next_quote(str, &i, str[i - 1]);
			i++;
		}
		else
			skip_token(str, &i);
	}
	return (nb_part);
}

// static int	str_next_part_len(char *str, int i)
// {
	
// }

// static char	**expand_split_part(char *str)
// {
// 	char	**split;

// 	split = ft_calloc(get_str_nb_part(str) + 1, sizeof(char *));
// 	if (split == NULL)
// 		return (NULL);
// 	return (split);
// }

char	**get_expanded_lex(char *str, t_env_list *env)
{
	char	*expanded_str;

	printf("nb_part = %d\n", get_str_nb_part(str));
	if (str[0] != '\'')
		expanded_str = replace_env_var(str, env);
	else
		expanded_str = ft_strdup(str);
	printf("%s\n", expanded_str);
	return (NULL);
}

char	**expand_new(char **lex, t_env_list *env)
{
	char	***lexers;
	int		i;

	(void) lexers;
	i = 0;
	while (lex[i] != NULL)
	{
		get_expanded_lex(lex[i], env);
		i++;
	}
	return (NULL);
}
