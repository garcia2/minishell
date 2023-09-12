/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:46:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/09/12 07:39:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_command_table(t_cmd_table *cmd_table)
{
	int	i;

	printf("PRINT COMMAND_TABLE -\n");
	printf("infile: %d\n", cmd_table->infile_fd);
	printf("infile: %d\n", cmd_table->outfile_fd);
	printf("cmd:");
	i = 0;
	while (cmd_table->cmd[i] != NULL)
	{
		printf(" [%s]", cmd_table->cmd[i]);
		i++;
	}
	printf("\n");
}

int	get_nb_dollars(char *str)
{
	int	nb_dollars;
	int	i;

	nb_dollars = 0;
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$' && str[i +1] != '\0' && str[i+1] != ' ')
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
	return (nb_dollars);
}

char **extract_dollars(char *str, t_env_list *env)
{
	char	**splited_str;
	int		i;
	int		j;
	int		k;

	(void) env;
	//printf("string = [%s]\nnb_dollars = %d\n", str, get_nb_dollars(str));
	splited_str = ft_calloc(get_nb_dollars(str) + 2, sizeof(char*));
	splited_str[get_nb_dollars(str)] = NULL;
	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = 1;
		while (str[i] == '$' && str[i + j] != '\0' && str[i + j] != '$' && str[i + j] != ' ')
				j++;
		while (str[i] != '$' && str[i + j] != '\0' && str[i + j] != '$')
				j++;
		splited_str[k] = ft_calloc(j + 1, sizeof(char));
		ft_strlcpy(splited_str[k], str + i, j + 1);
		splited_str[k][j + 1] = '\0';
		//printf("copy of [%s] at id=%d len=%d\n", str, i, j);
		//printf("%s\n", splited_str[k]);
		k++;
		i += j;
	}
	return (splited_str);
}

void	extract_dollars_tab_without_quote(char **new_tab, char *str, t_env_list *env, int *k)
{
	char	**temp_tab;
	int		i;

	temp_tab = extract_dollars(str, env);
	i = 0;
	while (temp_tab[i] != NULL)
	{
		new_tab[*k] = ft_strdup(temp_tab[i]);
		i++;
		(*k)++;
	}
	free_lexer(temp_tab);
}

char **extract_dollars_tab(char **tab, t_env_list *env)
{
	char	**new_tab;
	int		nb_dollars;
	int		i;
	int		k;

	nb_dollars = 0;
	i = 0;
	//print_lexer(tab);
	//printf("done\n");
	while (tab[i] != NULL)
	{
		if (!is_quote(tab[i][0]))
			nb_dollars += get_nb_dollars(tab[i]);
		else
			nb_dollars++;
		i++;
	}
	//printf("nb_dollars=%d\n", nb_dollars);
	new_tab = ft_calloc(nb_dollars + 1, sizeof(char *));
	i = 0;
	k = 0;
	while (tab[i] != NULL)
	{
		if (!is_quote(tab[i][0]))
			extract_dollars_tab_without_quote(new_tab, tab[i], env, &k);
		else
		{
			new_tab[k] = ft_strdup(tab[i]);
			k++;
		}
		i++;
	}
	new_tab[k] = NULL;
	return (new_tab);
}

int	get_len(char **tab)
{
	int	len;

	while (tab[len] != NULL)
		len++;
	return (len);
}

char **interpret_dolars(char **tab, t_env_list *env)
{
	char	**new_tab;
	int		i;
	
	new_tab = ft_calloc(get_len(tab) + 1, sizeof(char *));
	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '\'')
			new_tab[i] = ft_strdup(tab[i]);
		else
			new_tab[i] = replace_env_var(tab[i], env);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char **expand_process(char *str, t_env_list *env)
{
	char **tab;
	char **tab2;

	tab = extract_quotes(str);
	tab2 = extract_dollars_tab(tab, env);
	free_lexer(tab);
	tab = interpret_dolars(tab2, env);
	print_lexer(tab);
	return (tab);
}
