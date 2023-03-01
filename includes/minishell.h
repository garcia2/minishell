/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:25:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/01 16:20:48 by jileroux         ###   ########.fr       */
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

typedef struct s_cmd_table
{
	int					append;
	char				*infile;
	char				*here_doc;
	char				*outfile;
	char				**cmd;
	struct s_cmd_table	*next;
}	t_cmd_table;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

/*******************************************************\
|					PARSER FUNCTIONS					|
\*******************************************************/

t_cmd_table	*init_table(char **lex);
t_cmd_table	*parser(char **lex);
t_cmd_table	*init_node(void);
void		init_redir(char **lex, t_cmd_table *cmd_table, int *i, int *j);
int			cmd_size(char **lex);
int			ft_strcmp(char *s1, char *s2);
void		add_back(t_cmd_table **lst, t_cmd_table *new);
void		init_tab(char **lex, t_cmd_table *cmd_table);
int			is_delimiter(char *lex);
void		init_cmd(char **lex, t_cmd_table *cmd_table);
void		add_cmd(char **lex, char **cmd_table, int *i);
void		clear_lst(t_cmd_table **lst);

/*******************************************************\
|					LEXER FUNCTIONS						|
\*******************************************************/

int			is_white_space(char c);
int			count_token(char *str);
char		*get_env(char *str, int *i);
char		*replace_env_var(char *str);
int			convert_dolars(char **lex);
void		go_next_quote(char	*str, int *i);
void		go_next_double_quote(char	*str, int *i);
void		skip_white_space(char *str, int *i);
void		skip_token(char *str, int *i);
char		*split_with_simple_quotes(char *str, int *i);
char		*split_with_double_quotes(char *str, int *i);
char		*split_without_quotes(char *str, int *i);
char		**lexer(char *str);
void		free_lexer(char **lex);
void		print_lexer(char **lex);

/*******************************************************\
|					ENV_LIST FUNCTIONS					|
\*******************************************************/

void		env_lst_free_one(t_env_list *lst);
void		env_lst_clear(t_env_list **lst);
t_env_list	*env_lst_pop(t_env_list **lst, char *key);
int			env_lst_exists(t_env_list *lst, char *key);
int			env_lst_size(t_env_list *lst);
t_env_list	*env_lstlast(t_env_list *lst);
void		env_lst_add_back(t_env_list **lst, t_env_list *new);
t_env_list	*env_lstnew(char *key, char *value);
void		env_lst_print(t_env_list *lst);
t_env_list	*parse_env(char **envp);
char		*get_env_by_key(t_env_list *env_lst, char *key);

#endif
