/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:08:41 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 17:33:55 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_process(char *str, t_env_list *env)
{
	char	**tab;
	char	**tab2;
	char	*new_str;

	tab = extract_quotes(str);
	tab2 = extract_dollars_tab(tab);
	free_lexer(tab);
	tab = interpret_dolars(tab2, env);
	free_lexer(tab2);
	new_str = rejoin_expand(tab);
	free_lexer(tab);
	tab = split_spaces_witout_quotes(new_str);
	free(new_str);
	tab2 = erazer(tab);
	free_lexer(tab);
	return (tab2);
}

int	sizer(char **tab, t_env_list *env)
{
	int		i;
	int		j;
	int		malloc_len;
	char	**t_tab;

	malloc_len = 0;
	i = 0;
	while (tab[i])
	{
		t_tab = expand_process(tab[i], env);
		j = 0;
		while (t_tab[j])
		{
			malloc_len++;
			j++;
		}
		free_lexer(t_tab);
		i++;
	}
	return (malloc_len);
}

void	f_expand_command_table(t_cmd_table *cmd_table, t_env_list *env)
{
	char	**expanded_cmd;

	while (cmd_table != NULL)
	{
		if (cmd_table->cmd != NULL)
		{
			expanded_cmd = expands(cmd_table->cmd, env);
			free_lexer(cmd_table->cmd);
			cmd_table->cmd = expanded_cmd;
		}
		cmd_table = cmd_table->next;
	}
}

char	**expands(char **tab, t_env_list *env)
{
	int		i;
	int		j;
	int		k;
	char	**t_tab;
	char	**new_tab;

	if (tab == NULL)
		return (NULL);
	i = -1;
	k = 0;
	new_tab = malloc(sizeof(char *) * (sizer(tab, env) + 1));
	if (new_tab == NULL)
		return (0);
	while (tab[++i])
	{
		t_tab = expand_process(tab[i], env);
		j = -1;
		while (t_tab[++j])
			new_tab[k++] = strdup(t_tab[j]);
		free_lexer(t_tab);
	}
	new_tab[k] = NULL;
	return (new_tab);
}
