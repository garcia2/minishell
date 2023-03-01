LEXER_FILES = lexer.c \
			count_token.c \
			is_white_space.c \
			get_env.c \
			replace_env_var.c \
			skip.c \
			spliters.c

PARSER_FILES = parser.c\
			init_utils.c\
			init.c\
			free.c

SRCS_FILES = main.c

LEXER = $(addprefix srcs/lexer/, $(LEXER_FILES))

PARSER = $(addprefix srcs/parser/, $(PARSER_FILES))

SRCS = $(addprefix srcs/, $(SRCS_FILES))


LEXER_OBJS	= ${LEXER:.c=.o}

PARSER_OBJS	= ${PARSER:.c=.o}

SRCS_OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${LEXER_OBJS} ${PARSER_OBJS} ${SRCS_OBJS}
		make -C libft
		${CC} -o ${NAME} ${LEXER_OBJS} ${PARSER_OBJS} ${SRCS_OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME} bonus

clean:
		make clean -C libft
		${RM} ${LEXER_OBJS}

fclean:		clean
		make fclean -C libft
		${RM} ${NAME}

re:		clean all


.PHONY:		all clean fclea
