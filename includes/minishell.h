/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:25:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/03/30 12:16:58 by jileroux         ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_cmd_table
{
	int					infile_fd;
	int					outfile_fd;
	char				**cmd;
	struct s_cmd_table	*next;
}	t_cmd_table;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

int			launcher(void);
int			minishell(void);

void		do_exec(t_cmd_table *cmd_table);

/*******************************************************\
|					PARSER FUNCTIONS					|
\*******************************************************/

t_cmd_table	*init_node(void);
t_cmd_table	*parser(char **lex);
t_cmd_table	*init_table(char **lex);

int			cmd_size(char **lex);
char		*get_next_line(int fd);
int			is_delimiter(char *lex);
void		clear_lst(t_cmd_table **lst);
int			ft_strcmp(char *s1, char *s2);
int			compare_eof(char *s1, char *s2);
void		init_tab(char **lex, t_cmd_table *cmd_table);
void		init_cmd(char **lex, t_cmd_table *cmd_table);
void		add_back(t_cmd_table **lst, t_cmd_table *new);
void		add_cmd(char **lex, char **cmd_table, int *i);
int			here_doc_logic(t_cmd_table *cmd_table, char *limiter);
void		init_redir(char **lex, t_cmd_table *cmd_table, int *i);

/*******************************************************\
|					LEXER FUNCTIONS						|
\*******************************************************/

char		**lexer(char *str);
int			is_white_space(char c);
int			count_token(char *str);
void		free_lexer(char **lex);
void		print_lexer(char **lex);
int			convert_dolars(char **lex);
char		*replace_env_var(char *str);
char		*get_env(char *str, int *i);
void		skip_token(char *str, int *i);
void		go_next_quote(char	*str, int *i);
void		skip_white_space(char *str, int *i);
char		*split_without_quotes(char *str, int *i);
void		go_next_double_quote(char	*str, int *i);
char		*split_with_simple_quotes(char *str, int *i);
char		*split_with_double_quotes(char *str, int *i);

/*******************************************************\
|					EXEC FUNCTIONS						|
\*******************************************************/

int			pwd_cd(t_cmd_table *cmd_table);

/*******************************************************\
|					BUILTINS FUNCTIONS					|
\*******************************************************/

int			get_pwd(void);
int			change_directory(char *cmd);

/*******************************************************\
|					ENV_LIST FUNCTIONS					|
\*******************************************************/

t_env_list	*parse_env(char **envp);
t_env_list	*env_lstlast(t_env_list *lst);
t_env_list	*env_lstnew(char *key, char *value);
t_env_list	*env_lst_pop(t_env_list **lst, char *key);

int			env_lst_size(t_env_list *lst);
void		env_lst_print(t_env_list *lst);
void		env_lst_clear(t_env_list **lst);
void		env_lst_free_one(t_env_list *lst);
int			env_lst_exists(t_env_list *lst, char *key);
char		*get_env_by_key(t_env_list *env_lst, char *key);
void		env_lst_add_back(t_env_list **lst, t_env_list *new);

/*******************************************************\
|					SIGNAL FUNCTIONS					|
\*******************************************************/

void		init_signal(void);
void		handler_signal(int sig);

#endif
