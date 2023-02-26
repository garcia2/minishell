LEXER_FILES = lexer.c \
			count_token.c \
			is_white_space.c \
			get_env.c \
			replace_env_var.c \
			skip.c \
			spliters.c \
			convert_dolars.c

ENV_FILES	= env_parser.c \
			env_lst.c \
			env_lst_del.c \
			env_lst_print.c \
			ft_strcmp.c

LEXER = $(addprefix srcs/lexer/, $(LEXER_FILES))

ENV = $(addprefix srcs/env/, $(ENV_FILES))

MAIN		= srcs/main.c

LEXER_OBJS	= ${LEXER:.c=.o}

ENV_OBJS	= ${ENV:.c=.o}

MAIN_OBJS	= ${MAIN:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${LEXER_OBJS} ${ENV_OBJS} ${MAIN_OBJS}
		make -C libft
		${CC} -o ${NAME} ${LEXER_OBJS} ${ENV_OBJS} ${MAIN_OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME} bonus

clean:
		make clean -C libft
		${RM} ${LEXER_OBJS} ${ENV_OBJS} ${MAIN_OBJS}

fclean:		clean
		make fclean -C libft 
		${RM} ${NAME}

re:		clean all


.PHONY:		all clean fclean re