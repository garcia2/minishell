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
			get_env_tab.c

PARSER_FILES = parser.c\
			init_utils.c\
			here_doc.c\
			get_next_line.c \
			init.c\
			free.c\
			cmd_table_lst.c\
			open_files.c

EXEC_FILES = pwd_cd.c \
			exec.c \
			command.c \
			dup_files.c \
			exec_error.c

BUILTINS_FILES = cd.c\
				pwd.c\
				echo.c\
				export.c\
				builtin_util.c\
				unset.c

SRCS_FILES = main.c\
			launcher.c\
			signal.c

EXPAND_FILES = expand.c \
			replace_env_var.c \
			convert_dolars.c \
			get_env.c \
			delete_quotes.c \
			join_split.c \
			expand_cmd_table.c \
			re_lexing.c \
			get_nb_cmd.c \
			quote_map.c

LEXER = $(addprefix srcs/lexer/, $(LEXER_FILES))
PARSER = $(addprefix srcs/parser/, $(PARSER_FILES))
EXEC = $(addprefix srcs/exec/, $(EXEC_FILES))
BUILTINS = $(addprefix srcs/exec/builtins/, $(BUILTINS_FILES))
EXPAND = $(addprefix srcs/expand/, $(EXPAND_FILES))
ENV = $(addprefix srcs/env/, $(ENV_FILES))
SRCS = $(addprefix srcs/, $(SRCS_FILES))

LEXER_OBJS	= ${LEXER:.c=.o}
PARSER_OBJS	= ${PARSER:.c=.o}
EXEC_OBJS	= ${EXEC:.c=.o}
BUILTINS_OBJS	= ${BUILTINS:.c=.o}
EXPAND_OBJS	= ${EXPAND:.c=.o}
ENV_OBJS	= ${ENV:.c=.o}
SRCS_OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${LEXER_OBJS} ${PARSER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS}
		make -C libft
		${CC} -o ${NAME} ${LEXER_OBJS} ${PARSER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME} bonus

clean:
		make clean -C libft

		${RM} ${LEXER_OBJS} ${EXPAND_OBJS} ${ENV_OBJS} ${PARSER_OBJS} ${BUILTINS_OBJS} ${EXEC_OBJS} ${SRCS_OBJS}

fclean:		clean
		make fclean -C libft
		${RM} ${NAME}

re:		clean all

.PHONY:		all clean fclean

