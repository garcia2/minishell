/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_without_quotes_f.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:01:50 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/12 16:47:48 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
A remplacer char espace  par white_space 
*/
// int	get_nb_spaces_without_quotes(char *str)
// {
// 	int		nb_spaces;
// 	int		i;
// 	char	quote;

// 	i = 0;
// 	while (str[i] != '\0' && str[i] == ' ')
// 		i++;
// 	nb_spaces = (str[i] != '\0' && str[i] != ' ' && !is_quote(str[i]));
// 	while (str[i] != '\0')
// 	{
// 		if (is_quote(str[i]))
// 		{
// 			nb_spaces++;
// 			quote = str[i];
// 			i++;
// 			while (str[i] != '\0' && str[i] != quote)
// 				i++;
// 		}
// 		else
// 		{
// 			if (str[i] == ' ')
// 			{
// 				while (str[i] != '\0' && str[i] == ' ')
// 					i++;
// 				nb_spaces += str[i] != '\0';
// 			}
// 		}
// 		i += (str[i] != '\0');
// 	}
// 	return (nb_spaces);
// }

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// int	get_nb_spaces_without_quotes(char *str) {
//     int word_count = 0;
//     int in_quotes = 0; // 0 represents false, 1 represents double quotes, 2 represents single quotes

//     while (*str) {
//         if (*str == '"') {
//             if (in_quotes == 1) {
//                 in_quotes = 0;
//             } else if (in_quotes == 0) {
//                 in_quotes = 1;
//             }
//         } else if (*str == '\'') {
//             if (in_quotes == 2) {
//                 in_quotes = 0;
//             } else if (in_quotes == 0) {
//                 in_quotes = 2;
//             }
//         } else if (!in_quotes && is_whitespace(*str)) {
//             // Skip consecutive whitespace characters
//             while (is_whitespace(*str)) {
//                 str++;
//             }
//             word_count++;
//             continue;
//         }
//         str++;
//     }

//     // If the string ends with non-whitespace characters
//     // and it's not inside quotes, increment word_count.
//     if (!in_quotes && word_count > 0) {
//         word_count++;
//     }

//     return word_count;
// }

int	get_nb_spaces_without_quotes(char *str)
{
	int	is_in_quote;
	int	quote;
	int	i;
	int	nb_spaces;

	if (ft_strlen(str) == 0)
		return (0);
	nb_spaces = str[0] != ' ';
	is_in_quote = 0;
	if (is_quote(str[0]))
	{
		is_in_quote = 1;
		quote = str[0];
	}
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i - 1] == ' ' && !is_in_quote)
			nb_spaces++;
		if (is_quote(str[i]))
		{
			if (is_in_quote && str[i] == quote)
				is_in_quote = 0;
			else if (!is_in_quote)
			{
				is_in_quote = 1;
				quote = str[i];
			}
		}
		i++;
	}
	return (nb_spaces);
}

int	get_len_next_word(char *str, int i)
{
	int		is_in_quote;
	char	quote;
	int		j;

	if (str[i] == '\0')
		return (0);
	is_in_quote = 0;
	if (is_quote(str[i]))
	{
		is_in_quote = 1;
		quote = str[i];
	}
	j = 1;
	while (str[i + j] != '\0')
	{
		if (str[i + j] == ' ' && !is_in_quote)
			return (j);
		else if(is_quote(str[i + j]))
		{
			if (is_in_quote && str[i + j] == quote)
				is_in_quote = 0;
			else if (!is_in_quote)
			{
				is_in_quote = 1;
				quote = str[i];
			}
		}
		j++;
	}
	return (j);
}

char **split_spaces_witout_quotes(char *str)
{
	char	**splited_tab;
	int		i;
	int		len;
	int		k;

	(void) str;
	//TEST
	// printf("nb_space of [s] = %d\n", get_nb_spaces_without_quotes("s"));
	// printf("nb_space of [] = %d\n", get_nb_spaces_without_quotes(""));
	// printf("nb_space of [  sfwef] = %d\n", get_nb_spaces_without_quotes("  sfwef"));
	// printf("nb_space of [    ] = %d\n", get_nb_spaces_without_quotes("    "));
	// printf("nb_space of [\"Salut\"] = %d\n", get_nb_spaces_without_quotes("\"Salut\""));
	// printf("nb_space of [\"S a l ut\"] = %d\n", get_nb_spaces_without_quotes("\"S a l ut\""));
	// printf("nb_space of [\"S a l ut\" 'oui' et \"toi\"] = %d\n", get_nb_spaces_without_quotes("\"S a l ut\" 'oui' et \"toi\""));
	// printf("nb_space of [j\"ie  ie\"wjf   ] = %d\n", get_nb_spaces_without_quotes("j\"ie  ie\"wjf   "));
	// printf("nb_space of [    ewf wef ewf wef e  ] = %d\n", get_nb_spaces_without_quotes("    ewf wef ewf wef e  "));
	// 
	splited_tab = ft_calloc(get_nb_spaces_without_quotes(str) + 1, sizeof(char *));
	k = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] == ' ')
			i++;
		len = get_len_next_word(str, i);
		splited_tab[k] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(splited_tab[k], str + i, len + 1);
		splited_tab[k][len] = '\0';
		k++;
		i += len;
		// printf("len = %d\n", len);
		// printf("i = %d\n", i);
	}
	splited_tab[k] = NULL;
	return (splited_tab);
}