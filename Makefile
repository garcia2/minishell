SRCS_FILES = main.c \
			lexer.c \
			count_token.c \
			is_white_space.c \
			get_env.c

SRCS = $(addprefix srcs/, $(SRCS_FILES))

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= cc

LIBFT = libft/libft.a

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -I includes/ -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		make -C libft
		${CC} -o ${NAME} ${OBJS} -I includes/ -L. ${LIBFT} -L/usr/lib/x86_64-linux-gnu  -lreadline

all:		${NAME} bonus

clean:
		make clean -C libft
		${RM} ${OBJS}

fclean:		clean
		make fclean -C libft 
		${RM} ${NAME}

re:		clean all


.PHONY:		all clean fclean re