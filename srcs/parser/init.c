/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:21:22 by jileroux          #+#    #+#             */
/*   Updated: 2023/03/31 17:11:22 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(char **lex, t_cmd_table *cmd_table, int *i, t_env_list *env)
{
	while (lex[*i] && ft_strcmp(lex[*i], "|") != 0)
	{
		if (ft_strcmp(lex[*i], "<") == 0 && lex[*i + 1])
			open_infile(&(cmd_table->infile_fd), &(lex[*i + 1]), env);
		else if (ft_strcmp(lex[*i], "<<") == 0 && lex[*i + 1])
			here_doc_logic(cmd_table, lex[*i + 1]);
		else if (ft_strcmp(lex[*i], ">") == 0 && lex[*i + 1])
			open_outfile(&(cmd_table->outfile_fd), &(lex[*i + 1]), env);
		else if (ft_strcmp(lex[*i], ">>") == 0 && lex[*i + 1])
			open_append(&(cmd_table->outfile_fd), &(lex[*i + 1]), env);
		(*i)++;
	}
}

// void	init_redir(char **lex, t_cmd_table *cmd_table, int *i)
// {
// 	while (lex[*i] && ft_strcmp(lex[*i], "|") != 0)
// 	{
// 		if (ft_strcmp(lex[*i], "<") == 0 && lex[*i + 1])
// 		{
// 			if (cmd_table->infile_fd > 2)
// 				close(cmd_table->infile_fd);
// 			cmd_table->infile_fd = open(lex[*i + 1], O_RDONLY);
// 		}
// 		else if (ft_strcmp(lex[*i], "<<") == 0 && lex[*i + 1])
// 			here_doc_logic(cmd_table, lex[*i + 1]);
// 		else if (ft_strcmp(lex[*i], ">") == 0 && lex[*i + 1])
// 		{
// 			if (cmd_table->outfile_fd > 2)
// 				close(cmd_table->outfile_fd);
// 			cmd_table->outfile_fd = open(lex[*i + 1], O_WRONLY
// 					| O_CREAT | O_TRUNC, 0644);
// 		}
// 		else if (ft_strcmp(lex[*i], ">>") == 0 && lex[*i + 1])
// 		{
// 			if (cmd_table->outfile_fd > 2)
// 				close(cmd_table->outfile_fd);
// 			cmd_table->outfile_fd = open(lex[*i + 1], O_WRONLY
// 					| O_CREAT | O_APPEND, 0644);
// 		}
// 		(*i)++;
// 	}
// }

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
