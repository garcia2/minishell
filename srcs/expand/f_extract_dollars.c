/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_extract_dollars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:46:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/13 23:49:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_command_table(t_cmd_table *cmd_table)
// {
// 	int	i;

// 	printf("PRINT COMMAND_TABLE -\n");
// 	printf("infile: %d\n", cmd_table->infile_fd);
// 	printf("infile: %d\n", cmd_table->outfile_fd);
// 	printf("cmd:");
// 	i = 0;
// 	while (cmd_table->cmd[i] != NULL)
// 	{
// 		printf(" [%s]", cmd_table->cmd[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

int	get_nb_dollars(char *str)
{
	int	nb_dollars;
	int	i;

	nb_dollars = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '$')
		{
			nb_dollars++;
			i++;
			if (str[i] == '$')
				i++;
			else
			{
				while (str[i] != '\0' && str[i] != '$' && str[i] != ' ')
					i++;
			}
		}
		else
			i++;
	}
	return (nb_dollars + 1);
}

static int	extract_dollars_process(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i] == '$' && str[i + j] == '$')
		j++;
	while (str[i] == '$' && str[i + j] != '\0'
		&& str[i + j] != '$' && str[i + j] != ' ')
		j++;
	while (str[i] != '$' && str[i + j] != '\0' && str[i + j] != '$')
		j++;
	return (j);
}

// char	**extract_dollars(char *str)
// {
// 	char	**splited_str;
// 	int		i;
// 	int		j;
// 	int		k;

// 	splited_str = ft_calloc(get_nb_dollars(str) + 2, sizeof(char *));
// 	splited_str[get_nb_dollars(str)] = NULL;
// 	k = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		j = 1;
// 		while (str[i] == '$' && str[i + j] == '$')
// 			j++;
// 		while (str[i] == '$' && str[i + j] != '\0'
// 			&& str[i + j] != '$' && str[i + j] != ' ')
// 			j++;
// 		while (str[i] != '$' && str[i + j] != '\0' && str[i + j] != '$')
// 			j++;
// 		splited_str[k] = ft_calloc(j + 1, sizeof(char));
// 		ft_strlcpy(splited_str[k], str + i, j + 1);
// 		splited_str[k][j] = '\0';
// 		k++;
// 		i += j;
// 	}
// 	splited_str[k] = NULL;
// 	return (splited_str);
// }
char	**extract_dollars(char *str)
{
	char	**splited_str;
	int		i;
	int		j;
	int		k;

	splited_str = ft_calloc(get_nb_dollars(str) + 2, sizeof(char *));
	splited_str[get_nb_dollars(str)] = NULL;
	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = extract_dollars_process(str, i);
		splited_str[k] = ft_calloc(j + 1, sizeof(char));
		ft_strlcpy(splited_str[k], str + i, j + 1);
		splited_str[k][j] = '\0';
		k++;
		i += j;
	}
	splited_str[k] = NULL;
	return (splited_str);
}
