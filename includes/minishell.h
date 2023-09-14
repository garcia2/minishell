/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:25:26 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 23:08:29 by nigarcia         ###   ########.fr       */
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

extern int	g_error;

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

typedef struct s_pipex
{
	int	**pipes;
	int	*pids;
	int	nb_cmd;
	int	rfd;
	int	wfd;
	int	rdup;
	int	wdup;
	int	pid;
}	t_pipex;

int			launcher(t_env_list **env);
int			minishell(t_env_list **env);
int			delete_file(void);
void		do_exec(t_cmd_table *cmd_table, t_env_list **env);

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
int			add_cmd(char **lex, char **cmd_table, int *i);
int			init_tab(char **lex, t_cmd_table *cmd_table);
int			init_cmd(char **lex, t_cmd_table *cmd_table);
void		add_back(t_cmd_table **lst, t_cmd_table *new);
int			here_doc_logic(t_cmd_table *cmd_table, char *limiter);
void		init_redir(char **lex, t_cmd_table *cmd_table, int *i,
				t_env_list *env);
void		check_fd_opened(int fd);
void		check_fd_closed(int fd);
void		open_infile(int *fd, char **file_name, t_env_list *env);
void		open_outfile(int *fd, char **file_name, t_env_list *env);
void		open_append(int *fd, char **file_name, t_env_list *env);
int			init_here_doc(int *i, char **nb, char **temp_file_name);

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

void		child_exit(int pid, int *cnt);
int			dup_files(t_cmd_table *cmd_table);
int			pwd_cd(t_cmd_table *cmd_table, t_env_list *env);
void		print_no_such_file(char *cmd);
int			set_command_path(t_cmd_table *cmd_table, t_env_list *env);
int			dup_files(t_cmd_table *cmd_table);
int			exec_builtin(t_cmd_table *cmd_table, t_env_list **env,
				t_pipex *pipex, t_cmd_table *cmd_table_save);
void		do_exec_with_pipes(t_cmd_table *cmd_table, t_env_list **env);
void		exec_check_fd_close(void);
void		do_exec_without_pipe(t_cmd_table *cmd_table, t_env_list **env);
void		simple_exec(t_cmd_table *cmd_table, t_env_list **env,
				t_pipex *pipex, t_cmd_table *save);
int			exec_ppx_cmd(t_pipex *pipex, t_cmd_table *cmd_tab,
				t_env_list **env, t_cmd_table *cmd_table_save);
void		crit_exit(t_cmd_table *cmd_tab, t_env_list **env,
				t_pipex *pipex, int ec);

/*******************************************************\
|					BUILTINS FUNCTIONS					|
\*******************************************************/

int			is_builtin(char *str);
int			get_pwd(void);
int			change_directory(char *cmd, t_env_list *env);
int			export(t_env_list **env, char **args);
int			export_check_args(char	*args);
void		print_export_wrong_arg_error(char *arg);
int			unset(t_env_list **env, char	**args);
void		do_echo(t_cmd_table *cmd_table);

/*******************************************************\
|					EXPAND FUNCTIONS					|
\*******************************************************/

int			expand_cmd(char **str_ptr, t_env_list *env);
char		*get_env(char *str, int *i, t_env_list *env);
char		*replace_env_var(char *str, t_env_list *env);
int			convert_dolars(char **lex, t_env_list *env);
char		*join_split(char **split);
int			re_lexing_cmd(char ***cmd, int *quote_map);
int			get_nb_dollars(char *str);
char		**extract_dollars(char *str);
char		**extract_dollars_tab(char **tab);
char		**interpret_dolars(char **tab, t_env_list *env);
char		**extract_quotes(char *str);
char		*rejoin_expand(char **tab);
char		**split_spaces_witout_quotes(char *str);
int			get_len(char **tab);
char		**erazer(char **tab);
char		**expand_process(char *str, t_env_list *env);
char		**expands(char **tab, t_env_list *env);
void		f_expand_command_table(t_cmd_table *cmd_table, t_env_list *env);
void		mini_exit(t_cmd_table *cmd_table, t_env_list **env,
				t_pipex *pipex, t_cmd_table *cmd_table_save);

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
int			set_env_by_key(t_env_list *env_lst, char *key, char *new_value);
int			find_char(char *str, char c);
char		**get_env_tab(t_env_list *env);

/*******************************************************\
|					SIGNAL FUNCTIONS					|
\*******************************************************/

void		init_signal(void);
void		init_signal2(void);
void		handler_signal(int sig);
void		handler_heredoc(int sig);
void		signal_heredoc(int sig);

/*******************************************************\
|					ERROR FUNCTIONS						|
\*******************************************************/

int			exit_value(char **lex);
void		print_error(char *str);
void		print_command_not_found_error(char *cmd);

/*******************************************************\
|					PIPEX FUNCTIONS						|
\*******************************************************/

int			**get_pipes(int nb_pipes);
void		free_pipes(int **pipes, int nb_pipes);
void		close_pipes_not_used(t_pipex *pipex);
int			waitforit(t_pipex *pipex);
t_pipex		*get_pipex(int nb_cmd);
void		free_pipex(t_pipex *pipex);
void		close_pipex_dup(t_pipex *pipex);
void		close_all_pipes(t_pipex *pipex);
int			ft_dup(t_pipex *pipex, int pid);
int			pipex_process(t_pipex *pipex, t_cmd_table *cmd_table,
				t_env_list **env);

#endif
