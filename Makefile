LEXER_FILES = main.c \
			lexer.c \
			count_token.c \
			is_white_space.c \
			get_env.c

LEXER = $(addprefix srcs/lexer/, $(LEXER_FILES))

LEXER_OBJS	= ${LEXER:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${LEXER_OBJS}
		make -C libft
		${CC} -o ${NAME} ${LEXER_OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME} bonus

clean:
		make clean -C libft
		${RM} ${LEXER_OBJS}

fclean:		clean
		make fclean -C libft 
		${RM} ${NAME}

re:		clean all


.PHONY:		all clean fclean re