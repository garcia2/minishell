/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:25:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/24 17:40:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

int		is_white_space(char c);
int		count_token(char *str);
char	*get_env(char *str, int *i);
char	*replace_env_var(char *str);
void	go_next_quote(char	*str, int *i);
void	go_next_double_quote(char	*str, int *i);
void	skip_white_space(char *str, int *i);
void	skip_token(char *str, int *i);
char	*split_with_simple_quotes(char *str, int *i);
char	*split_with_double_quotes(char *str, int *i);
char	*split_without_quotes(char *str, int *i);
char	**lexer(char *str);
void	free_lexer(char **lex);
void	print_lexer(char **lex);

#endif