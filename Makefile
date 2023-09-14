LEXER_FILES = lexer.c \
			count_token.c \
			check_char.c \
			skip.c \
			spliters.c \
			check_lexer.c

ENV_FILES	= env_parser.c \
			env_lst.c \
			env_lst_del.c \
			env_lst_print.c \
			get_env_tab.c \
			get_set_env_by_key.c

PARSER_FILES = parser.c\
			init_utils.c\
			here_doc.c\
			init.c\
			free.c\
			cmd_table_lst.c\
			open_files.c

EXEC_FILES = pwd_cd.c \
			exec.c \
			exec_with_pipes.c \
			exec_without_pipe.c \
			command.c \
			dup_files.c \
			exutil.c \
			exec_error.c\
			exec_end.c

BUILTINS_FILES = cd.c\
				pwd.c\
				echo.c\
				export.c\
				export_error.c\
				builtin_util.c\
				unset.c\
				exit.c

SRCS_FILES = main.c\
			exit.c\
			signal.c\
			launcher.c

EXPAND_FILES = expand.c \
			replace_env_var.c \
			convert_dolars.c \
			get_env.c \
			join_split.c \
			f_extract_dollars.c \
			f_extract_dollars_tab.c \
			f_interpret_dollars.c \
			f_extract_quotes.c \
			f_rejoin_expand.c \
			f_split_space_without_quotes.c \
			f_delete_quotes.c \
			f_expand.c \

PIPEX_FILES = pipe.c \
			pipex.c \
			pipex_process.c \
			wait.c \
			dup.c

LEXER = $(addprefix srcs/lexer/, $(LEXER_FILES))
PARSER = $(addprefix srcs/parser/, $(PARSER_FILES))
EXEC = $(addprefix srcs/exec/, $(EXEC_FILES))
BUILTINS = $(addprefix srcs/exec/builtins/, $(BUILTINS_FILES))
EXPAND = $(addprefix srcs/expand/, $(EXPAND_FILES))
ENV = $(addprefix srcs/env/, $(ENV_FILES))
PIPEX = $(addprefix srcs/exec/pipex/, $(PIPEX_FILES))
SRCS = $(addprefix srcs/, $(SRCS_FILES))

LEXER_OBJS	= ${LEXER:.c=.o}
PARSER_OBJS	= ${PARSER:.c=.o}
EXEC_OBJS	= ${EXEC:.c=.o}
BUILTINS_OBJS	= ${BUILTINS:.c=.o}
EXPAND_OBJS	= ${EXPAND:.c=.o}
ENV_OBJS	= ${ENV:.c=.o}
PIPEX_OBJS	= ${PIPEX:.c=.o}
SRCS_OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${LEXER_OBJS} ${PARSER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${PIPEX_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS}
		make -C libft
		${CC} -o ${NAME} ${LEXER_OBJS} ${PARSER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${PIPEX_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME}

clean:
		make clean -C libft

		${RM} ${LEXER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${PIPEX_OBJS} ${PARSER_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS}

fclean:		clean
		make fclean -C libft
		${RM} ${NAME}

re:		clean all

.PHONY:		all clean fclean

