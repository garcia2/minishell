/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:25:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/04/08 14:09:14 by nigarcia         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

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

int			launcher(t_env_list *env);
int			minishell(t_env_list *env);

void		do_exec(t_cmd_table *cmd_table, t_env_list *env);

/*******************************************************\
|					PARSER FUNCTIONS					|
\*******************************************************/

t_cmd_table	*init_node(void);
t_cmd_table	*parser(char **lex, t_env_list *env);
t_cmd_table	*init_table(char **lex, t_env_list *env);

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
void		init_redir(char **lex, t_cmd_table *cmd_table, int *i,
				t_env_list *env);
void		check_fd_opened(int fd);
void		open_infile(int *fd, char **file_name, t_env_list *env);
void		open_outfile(int *fd, char **file_name, t_env_list *env);
void		open_append(int *fd, char **file_name, t_env_list *env);

/*******************************************************\
|					LEXER FUNCTIONS						|
\*******************************************************/

int			is_white_space(char c);
int			is_spec_char(char c);
int			is_quote(char c);
int			count_token(char *str);
void		go_next_quote(char	*str, int *i, char quote);
void		skip_white_space(char *str, int *i);
void		skip_token(char *str, int *i);
int			split_lexer(char **lex, char *str);
char		**lexer(char *str);
void		free_lexer(char **lex);
void		print_lexer(char **lex);
int			check_lexer(char **lex);

/*******************************************************\
|					EXEC FUNCTIONS						|
\*******************************************************/

int			pwd_cd(t_cmd_table *cmd_table);
int			set_command_path(t_cmd_table *cmd_table, t_env_list *env);
int			dup_files(t_cmd_table *cmd_table);

/*******************************************************\
|					BUILTINS FUNCTIONS					|
\*******************************************************/

int			is_builtin(char *str);
int			get_pwd(void);
int			change_directory(char *cmd);
int			export(t_env_list *env, char **args);
int			unset(t_env_list *env, char	**args);
void		do_echo(t_cmd_table *cmd_table);

/*******************************************************\
|					EXPAND FUNCTIONS					|
\*******************************************************/

int			expand_cmd(char **str_ptr, t_env_list *env);
char		*get_env(char *str, int *i, t_env_list *env);
char		*replace_env_var(char *str, t_env_list *env);
int			convert_dolars(char **lex, t_env_list *env);
int			delete_quotes(char **split);
char		*join_split(char **split);
void		expand_cmd_tables(t_cmd_table *cmd_tab, t_env_list *env);
int			re_lexing_cmd(char ***cmd, int *quote_map);
int			get_nb_cmd(char **cmds);
int			get_lexers_nb_cmd(char ***lexs);
int			*get_quote_map(char **lex);

/*******************************************************\
|					ENV_LIST FUNCTIONS					|
\*******************************************************/

t_env_list	*parse_env(char **envp);
t_env_list	*env_lstlast(t_env_list *lst);
t_env_list	*env_lstnew(char *key, char *value);
t_env_list	*env_lst_pop(t_env_list **lst, char *key);

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
int			find_char(char *str, char c);
char		**get_env_tab(t_env_list *env);

/*******************************************************\
|					SIGNAL FUNCTIONS					|
\*******************************************************/

void		init_signal(void);
void		handler_signal(int sig);

/*******************************************************\
|					ERROR FUNCTIONS						|
\*******************************************************/

void		print_error(char *str);
void		print_command_not_found_error(char *cmd);

#endif
