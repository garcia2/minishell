/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:21:22 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/01 15:58:27 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(char **lex, t_cmd_table *cmd_table, int *i, int *j)
{
	while (lex[*i] && ft_strcmp(lex[*i], "|") != 0)
	{
		if (ft_strcmp(lex[*i], "<") == 0 && lex[*i + 1])
			cmd_table->infile = ft_strdup(lex[(*i)++ + 1]);
		else if (ft_strcmp(lex[*i], "<<") == 0 && lex[*i + 1])
			cmd_table->here_doc = ft_strdup(lex[(*i)++ + 1]);
		else if (ft_strcmp(lex[*i], ">") == 0 && lex[*i + 1])
			cmd_table->outfile = ft_strdup(lex[(*i)++ + 1]);
		else if (ft_strcmp(lex[*i], ">>") == 0 && lex[*i + 1])
		{
			cmd_table->outfile = ft_strdup(lex[(*i)++ + 1]);
			cmd_table->append = 1;
		}
		(*i)++;
		(*j)++;
	}
}

static int	count_element(char **lex, int *i)
{
	int	element;

	element = 0;
	if (!is_delimiter(lex[*i]))
		element++;
	(*i)++;
	while (lex[*i] && ft_strcmp(lex[*i], "|") != 0)
	{
		if (!is_delimiter(lex[*i]) && !is_delimiter(lex[*i - 1]))
			element++;
		(*i)++;
	}
	return (element);
}

void	add_cmd(char **lex, char **cmd, int *i)
{
	int	j;

	j = 0;
	if (!is_delimiter(lex[*i]))
			cmd[j++] = ft_strdup(lex[*i]);
	(*i)++;
	while (lex[*i] && ft_strcmp(lex[*i], "|") != 0)
	{
		if (!is_delimiter(lex[*i]) && !is_delimiter(lex[*i - 1]))
		{
			cmd[j] = ft_strdup(lex[*i]);
			j++;
		}
		(*i)++;
	}
	cmd[j] = NULL;
}

void	init_cmd(char **lex, t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (lex[i])
		{
			add_cmd(lex, cmd_table->cmd, &i);
			cmd_table = cmd_table->next;
			if (lex[i])
				i++;
		}
	}
}

void	init_tab(char **lex, t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		cmd_table->cmd = malloc(sizeof(char *) * (count_element(lex, &i) + 1));
		if (lex[i])
		{
			cmd_table = cmd_table->next;
			i++;
		}
	}
}
